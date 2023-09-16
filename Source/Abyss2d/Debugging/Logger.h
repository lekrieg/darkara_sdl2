// ////////////////////////
// File: Logger.h
// Created at: 09 15, 2023
// Description:
// Modified by: Daniel Henrique
// 09 15, 2023
// ////////////////////////

#ifndef LOGGER_H
#define LOGGER_H

	constexpr unsigned char LOG_FLAG_WRITE_TO_LOG_FILE = 1 << 0;
	constexpr unsigned char LOG_FLAG_WRITE_TO_DEBUGGER = 1 << 1;

	#include <string>

	namespace Logger
	{
		class ErrorMessenger
		{
		private:
			bool _enabled;

		public:
			ErrorMessenger(void);
			void Show(const std::string& errorMessage, bool isFatal, const char* funcName, const char* sourceFile, unsigned int lineNum);
		};

		void Init(const char* loggingConfigFilename);
		void Destroy(void);

		void Log(const std::string& tag, const std::string& message, const char* funcName, const char* sourceFile,
		         unsigned int lineNum);
		void SetDisplayFlags(const std::string& tag, unsigned char flags);
	}

	#define ABYSS_FATAL(str) \
		do \
		{ \
			static Logger::ErrorMessenger* pErrorMessenger = new(_NORMAL_BLOCK,__FILE__, __LINE__) Logger::ErrorMessenger; \
			std::string s((str)); \
			pErrorMessenger->Show(s, true, __FUNCTION__, __FILE__, __LINE__); \
		} \
		while (0) \
		
	#ifdef _DEBUG

		#define ABYSS_ERROR(str) \
			do \
			{ \
				static Logger::ErrorMessenger* pErrorMessenger = new(_NORMAL_BLOCK, __FILE__, __LINE__) Logger::ErrorMessenger; \
				std::string s((str)); \
				pErrorMessenger->Show(s, false, __FUNCTION__, __FILE__, __LINE__); \
			} \
			while (0) \
			
		#define ABYSS_WARNING(str) \
			do \
			{ \
				std::string s((str)); \
				Logger::Log("WARNING", s, __FUNCTION__, __FILE__, __LINE__); \
			} \
			while (0) \
			
		#define ABYSS_INFO(str) \
			do \
			{ \
				std::string s((str)); \
				Logger::Log("INFO", s, nullptr, nullptr, 0); \
			} \
			while (0) \
			
		#define ABYSS_LOG(tag, str) \
			do \
			{ \
				std::string s((str)); \
				Logger::Log(tag, s, nullptr, nullptr, 0); \
			} \
			while (0) \
			
		#define ABYSS_ASSERT(expr) \
			do \
			{ \
				if (!(expr)) \
				{ \
					static Logger::ErrorMessenger* pErrorMessenger = new(_NORMAL_BLOCK, __FILE__, __LINE__) Logger::ErrorMessenger; \
					pErrorMessenger->Show(#expr, false, __FUNCTION__, __FILE__, __LINE__); \
				} \
			} \
			while (0) \
		
	#else

		#define ABYSS_ERROR(str) do { (void)sizeof(str); } while(0) 
		#define ABYSS_WARNING(str) do { (void)sizeof(str); } while(0) 
		#define ABYSS_INFO(str) do { (void)sizeof(str); } while(0) 
		#define ABYSS_LOG(tag, str) do { (void)sizeof(tag); (void)sizeof(str); } while(0) 
		#define ABYSS_ASSERT(expr) do { (void)sizeof(expr); } while(0)

	#endif

#endif // !LOGGER_H
