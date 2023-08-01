#pragma once
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#include "FileIO.h"

#define INFO_LOG { bls::g_logger.Log(bls::LogLevel::Info, __FILE__, __LINE__); }
#define WARNING_LOG { bls::g_logger.Log(bls::LogLevel::Warning, __FILE__, __LINE__); }
#define ERROR_LOG { bls::g_logger.Log(bls::LogLevel::Error, __FILE__, __LINE__); }
#define ASSERT_LOG { bls::g_logger.Log(bls::LogLevel::Assert, __FILE__, __LINE__); }

namespace bls 
{

	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger
	{

	public:
		Logger(LogLevel logLevel, std::ostream* ostream) :
			m_logLevel{ logLevel },
			m_ostream{ ostream } 
		{}

		bool Log(LogLevel logLevel, std::string filename, int line);

	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;

	};

	extern Logger g_logger;
}