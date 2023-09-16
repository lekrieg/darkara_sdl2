#include "Logger.h"

#include <list>
#include <map>
#include <crtdbg.h>
#include <tinyxml2.h>

#include "../Multicore/CriticalSection.h"

static const char* ERROR_LOG_FILENAME = "error.log";

#ifdef _DEBUG
constexpr unsigned char ERROR_FLAG_DEFAULT = LOG_FLAG_WRITE_TO_DEBUGGER;
constexpr unsigned char WARNING_FLAG_DEFAULT = LOG_FLAG_WRITE_TO_DEBUGGER;
constexpr unsigned char LOG_FLAG_DEFAULT = LOG_FLAG_WRITE_TO_DEBUGGER;

#elif NDEBUG
constexpr unsigned char ERROR_FLAG_DEFAULT = (LOG_FLAG_WRITE_TO_DEBUGGER | LOG_FLAG_WRITE_TO_LOG_FILE);
constexpr unsigned char WARNING_FLAG_DEFAULT = (LOG_FLAG_WRITE_TO_DEBUGGER | LOG_FLAG_WRITE_TO_LOG_FILE);
constexpr unsigned char LOG_FLAG_DEFAULT = (LOG_FLAG_WRITE_TO_DEBUGGER | LOG_FLAG_WRITE_TO_LOG_FILE);

#else
const unsigned char ERROR_FLAG_DEFAULT = 0;
const unsigned char WARNING_FLAG_DEFAULT = 0;
const unsigned char LOG_FLAG_DEFAULT = 0;
#endif

class LogManager;
static LogManager *pLogManager = nullptr;

class LogManager
{
public:
	enum ErrorDialogResult
	{
		LOG_MANAGER_ERROR_ABORT,
		LOG_MANAGER_ERROR_RETRY,
		LOG_MANAGER_ERROR_IGNORE
	};

	typedef std::map<std::string, unsigned char> Tags;
	typedef std::list<Logger::ErrorMessenger*> ErrorMessengerList;

	Tags m_tags;
	ErrorMessengerList m_errorMessengers;

	CriticalSection m_tagCriticalSection;
	CriticalSection m_messengerCriticalSection;

public:
	// construction
	LogManager(void);
	~LogManager(void);
	void Init(const char* loggingConfigFilename);

	// logs
	void Log(const std::string& tag, const std::string& message, const char* funcName, const char* sourceFile, unsigned int lineNum);
	void SetDisplayFlags(const std::string& tag, unsigned char flags);

	// error messengers
	void AddErrorMessenger(Logger::ErrorMessenger* pMessenger);
	ErrorDialogResult Error(const std::string& errorMessage, bool isFatal, const char* funcName, const char* sourceFile, unsigned int lineNum);
private:
	// log helpers
	void OutputFinalBufferToLogs(const std::string& finalBuffer, unsigned char flags);
	void WriteToLogFile(const std::string& data);
	void GetOutputBuffer(std::string& outOutputBuffer, const std::string& tag, const std::string& message, const char* funcName, const char* sourceFile, unsigned int lineNum);
};

LogManager::LogManager()
{
	// set up the default log tags
	SetDisplayFlags("ERROR", ERROR_FLAG_DEFAULT);
	SetDisplayFlags("WARNING", WARNING_FLAG_DEFAULT);
	SetDisplayFlags("INFO", LOG_FLAG_DEFAULT);
}

LogManager::~LogManager()
{
	m_messengerCriticalSection.Lock();
	for (auto it = m_errorMessengers.begin(); it != m_errorMessengers.end(); ++it)
	{
		Logger::ErrorMessenger* pMessenger = (*it);
		delete pMessenger;
	}
	m_errorMessengers.clear();
	m_messengerCriticalSection.Unlock();
}

//------------------------------------------------------------------------------------------------------------------------------------
// Initializes the logger.
//------------------------------------------------------------------------------------------------------------------------------------
void LogManager::Init(const char* loggingConfigFilename)
{
	if (loggingConfigFilename)
	{
		tinyxml2::XMLDocument loggingConfigFile;
		if (loggingConfigFile.LoadFile(loggingConfigFilename) == tinyxml2::XML_SUCCESS)
		{
			tinyxml2::XMLElement* pRoot = loggingConfigFile.RootElement();
			if (!pRoot)
				return;

			// Loop through each child element and load the component
			for (tinyxml2::XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
			{
				unsigned char flags = 0;
				std::string tag(pNode->Attribute("tag"));

				if (pNode->Attribute("debugger"))
					flags |= LOG_FLAG_WRITE_TO_DEBUGGER;

				if (pNode->Attribute("file"))
					flags |= LOG_FLAG_WRITE_TO_LOG_FILE;

				SetDisplayFlags(tag, flags);
			}
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
// This function builds up the log string and outputs it to various places based on the display flags (m_displayFlags).
//------------------------------------------------------------------------------------------------------------------------------------
void LogManager::Log(const std::string& tag, const std::string& message, const char* funcName, const char* sourceFile, unsigned int lineNum)
{
	m_tagCriticalSection.Lock();
	Tags::iterator findIt = m_tags.find(tag);
	if (findIt != m_tags.end())
	{
		m_tagCriticalSection.Unlock();
		
		std::string buffer;
		GetOutputBuffer(buffer, tag, message, funcName, sourceFile, lineNum);
		OutputFinalBufferToLogs(buffer, findIt->second);
	}
	else
	{
		// Critical section is exited in the if statement above, so we need to exit it here if that didn't 
		// get executed.
		m_tagCriticalSection.Unlock();
	}
}  // end LogManager::Log()

//------------------------------------------------------------------------------------------------------------------------------------
// Sets one or more display flags
//------------------------------------------------------------------------------------------------------------------------------------
void LogManager::SetDisplayFlags(const std::string& tag, unsigned char flags)
{
	m_tagCriticalSection.Lock();
	if (flags != 0)
	{
		Tags::iterator findIt = m_tags.find(tag);
		if (findIt == m_tags.end())
			m_tags.insert(std::make_pair(tag, flags));
		else
			findIt->second = flags;
	}
	else
	{
		m_tags.erase(tag);
	}
	m_tagCriticalSection.Unlock();
}

//------------------------------------------------------------------------------------------------------------------------------------
// Adds an error messenger to the list
//------------------------------------------------------------------------------------------------------------------------------------
void LogManager::AddErrorMessenger(Logger::ErrorMessenger* pMessenger)
{
	m_messengerCriticalSection.Lock();
	m_errorMessengers.push_back(pMessenger);
	m_messengerCriticalSection.Unlock();
}


//------------------------------------------------------------------------------------------------------------------------------------
// Helper for ErrorMessenger.
//------------------------------------------------------------------------------------------------------------------------------------
LogManager::ErrorDialogResult LogManager::Error(const std::string& errorMessage, bool isFatal, const char* funcName, const char* sourceFile, unsigned int lineNum)
{
	std::string tag = ((isFatal) ? ("FATAL") : ("ERROR"));

	// buffer for our final output string
	std::string buffer;
	GetOutputBuffer(buffer, tag, errorMessage, funcName, sourceFile, lineNum);

	// write the final buffer to all the various logs
	m_tagCriticalSection.Lock();
	Tags::iterator findIt = m_tags.find(tag);
	if (findIt != m_tags.end())
		OutputFinalBufferToLogs(buffer, findIt->second);
	m_tagCriticalSection.Unlock();

    // show the dialog box
    int result = ::MessageBoxA(nullptr, buffer.c_str(), tag.c_str(), MB_ABORTRETRYIGNORE|MB_ICONERROR|MB_DEFBUTTON3);

	// act upon the choice
	switch (result)
	{
		case IDIGNORE : return LogManager::LOG_MANAGER_ERROR_IGNORE;
		case IDABORT  : __debugbreak(); return LogManager::LOG_MANAGER_ERROR_ABORT;  // assembly language instruction to break into the debugger
		case IDRETRY :	return LogManager::LOG_MANAGER_ERROR_RETRY;
		default :       return LogManager::LOG_MANAGER_ERROR_RETRY;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------
// This is a helper function that checks all the display flags and outputs the passed in finalBuffer to the appropriate places.
// 
// IMPORTANT: The two places this function is called from wrap the code in the tag critical section (m_pTagCriticalSection), 
// so that makes this call thread safe.  If you call this from anywhere else, make sure you wrap it in that critical section.
//------------------------------------------------------------------------------------------------------------------------------------
void LogManager::OutputFinalBufferToLogs(const std::string& finalBuffer, unsigned char flags)
{
	// Write the log to each display based on the display flags
	if ((flags & LOG_FLAG_WRITE_TO_LOG_FILE) > 0)  // log file
		WriteToLogFile(finalBuffer);
	if ((flags & LOG_FLAG_WRITE_TO_DEBUGGER) > 0)  // debugger output window
        ::OutputDebugStringA(finalBuffer.c_str());
}


//------------------------------------------------------------------------------------------------------------------------------------
// This is a helper function that writes the data string to the log file.
//------------------------------------------------------------------------------------------------------------------------------------
void LogManager::WriteToLogFile(const std::string& data)
{
    FILE* pLogFile = nullptr;
    fopen_s(&pLogFile, ERROR_LOG_FILENAME, "a+");
    if (!pLogFile)
        return;  // can't write to the log file for some reason

    fprintf_s(pLogFile, data.c_str());

    fclose(pLogFile);
}

//------------------------------------------------------------------------------------------------------------------------------------
// Fills outOutputBuffer with the find error string.
//------------------------------------------------------------------------------------------------------------------------------------
void LogManager::GetOutputBuffer(std::string& outOutputBuffer, const std::string& tag, const std::string& message, const char* funcName, const char* sourceFile, unsigned int lineNum)
{
	if (!tag.empty())
		outOutputBuffer = "[" + tag + "] " + message;
	else
		outOutputBuffer = message;

	if (funcName != NULL)
	{
		outOutputBuffer += "\nFunction: ";
		outOutputBuffer += funcName;
	}
	if (sourceFile != NULL)
	{
		outOutputBuffer += "\n";
		outOutputBuffer += sourceFile;
	}
	if (lineNum != 0)
	{
		outOutputBuffer += "\nLine: ";
        char lineNumBuffer[11];
        memset(lineNumBuffer, 0, sizeof(char));
		outOutputBuffer += std::to_string(_itoa_s(lineNum, lineNumBuffer, 10));
	}
	
	outOutputBuffer += "\n";
}

//-----------------------------------------------------------------------------------------------------------------------
// ErrorMessenger
//-----------------------------------------------------------------------------------------------------------------------
Logger::ErrorMessenger::ErrorMessenger(void)
{
	pLogManager->AddErrorMessenger(this);
	_enabled = true;
}

void Logger::ErrorMessenger::Show(const std::string& errorMessage, bool isFatal, const char* funcName, const char* sourceFile, unsigned int lineNum)
{
	if (_enabled)
	{
		if (pLogManager->Error(errorMessage, isFatal, funcName, sourceFile, lineNum) == LogManager::LOG_MANAGER_ERROR_IGNORE)
			_enabled = false;
	}
}

namespace Logger {

	void Init(const char* loggingConfigFilename)
	{
		if (!pLogManager)
		{
#ifdef _DEBUG
			pLogManager = new(_NORMAL_BLOCK, __FILE__, __LINE__) LogManager;
#else
			pLogManager = new LogManager;
#endif
			
			pLogManager->Init(loggingConfigFilename);
			
		}
	}

	void Destroy(void)
	{
		delete pLogManager;
		pLogManager = nullptr;
	}

	void Log(const std::string& tag, const std::string& message, const char* funcName, const char* sourceFile, unsigned int lineNum)
	{
		ABYSS_ASSERT(pLogManager);
		pLogManager->Log(tag, message, funcName, sourceFile, lineNum);
	}

	void SetDisplayFlags(const std::string& tag, unsigned char flags)
	{
		ABYSS_ASSERT(pLogManager);
		pLogManager->SetDisplayFlags(tag, flags);
	}

}  // end namespace Logger