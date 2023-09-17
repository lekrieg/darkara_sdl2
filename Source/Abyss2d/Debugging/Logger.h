// ////////////////////////
// File: Logger.h
// Created at: 09 15, 2023
// Description:
// Modified by: Daniel Henrique
// 09 15, 2023
// ////////////////////////

#ifndef LOGGER_H
#define LOGGER_H

	#include <string>

#include "../Utils/CommonStuff.h"

enum LogFlag
	{
		WriteToLogFile,
		WriteToDebugger
	};

	namespace logger
	{
		void Init(const char* loggingConfigFilename);
		void Destroy();

		template<typename ... Args>
		void Log(const LogFlag flag, const std::string& tag, const std::string& message, const char* format, Args ... args);
	}

	#define ABYSS_ASSERT assert
	#define ABYSS_STATIC_ASSERT static_assert
		
	#ifdef _DEBUG
		#define ABYSS_LOG(tag, flag, message, ...) \
		logger::Log(flag, tag, message, ##__VA_ARGS__);
		
		#define ABYSS_WARNING(flag, message, ...) ABYSS_LOG("warning", flag, message, ##__VA_ARGS__)
		#define ABYSS_ERROR(flag, message, ...) ABYSS_LOG("error", flag, message, ##__VA_ARGS__)
		#define ABYSS_INFO(flag, message, ...) ABYSS_LOG("info", flag, message, ##__VA_ARGS__)
	#else
		#define ABYSS_INFO
		#define ABYSS_ERROR
		#define ABYSS_WARNING
	#endif

// ----
#include <cstdarg>

class LogManager;
static LogManager *pLogManager = nullptr;

class LogManager
{
private:
	std::string fileName;

public:
	LogManager() = default;
	~LogManager() = default;
	
	void Init(const char* loggingConfigFilename);
	template<typename ... Args>
	void Log(const LogFlag flag, const std::string& tag, const std::string& message, const char* format, Args ... args);

private:
	template<typename ... Args>
	void OutputFinalBufferToLogs(const LogFlag flag, const std::string& finalBuffer, const char* format, Args ... args);
	template<typename ... Args>
	void WriteToLogFile(const std::string& data, const char* format, Args ... args);
	void GetOutputBuffer(std::string& outOutputBuffer, const std::string& tag, const std::string& message);
};

template<typename ... Args>
void LogManager::Log(const LogFlag flag, const std::string& tag, const std::string& message, const char* format, Args ... args)
{
	std::string buffer;
	GetOutputBuffer(buffer, tag, message);
	OutputFinalBufferToLogs(flag, buffer, format, std::forward<Args>(args)...);
}

template<typename ... Args>
void LogManager::OutputFinalBufferToLogs(const LogFlag flag, const std::string& finalBuffer, const char* format, Args ... args)
{
	if (flag == LogFlag::WriteToLogFile)
	{
		WriteToLogFile(finalBuffer, format, std::forward<Args>(args)...);
	}
	else if (flag == LogFlag::WriteToDebugger)
	{
		fprintf(stderr, finalBuffer.c_str(), std::forward<Args>(args)...);
	}
}

template<typename ... Args>
void LogManager::WriteToLogFile(const std::string& data, const char* format, Args ... args)
{
    FILE* pLogFile = nullptr;
    fopen_s(&pLogFile, fileName.c_str(), "a+");
    if (!pLogFile)
    {
    	return;
    }

    fprintf(pLogFile, data.c_str(), std::forward<Args>(args)...);
	
    fclose(pLogFile);
}

namespace logger {
	template<typename ... Args>
	void Log(const LogFlag flag, const std::string& tag, const std::string& message, const char* format, Args ... args)
	{
		pLogManager->Log(flag, tag, message, format, std::forward<Args>(args)...);
	}
}

#endif // !LOGGER_H
