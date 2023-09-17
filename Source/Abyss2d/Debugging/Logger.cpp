#include "Logger.h"

void LogManager::Init(const char* loggingConfigFilename)
{
	if (loggingConfigFilename)
	{
		fileName = loggingConfigFilename;
	}
}

void LogManager::GetOutputBuffer(std::string& outOutputBuffer, const std::string& tag, const std::string& message)
{
	if (!tag.empty())
	{
		outOutputBuffer = "[" + tag + "] " + message;
	}
	else
	{
		outOutputBuffer = message;
	}
	
	outOutputBuffer += "\n";
}

namespace logger {
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

	void Destroy()
	{
		delete pLogManager;
		pLogManager = nullptr;
	}
}