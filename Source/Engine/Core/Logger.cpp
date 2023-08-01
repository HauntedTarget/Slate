#include "Logger.h"


namespace bls 
{
	Logger g_logger(LogLevel::Info, &std::cout);

	bool Logger::Log(LogLevel logLevel, std::string filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case LogLevel::Info:
			*m_ostream << "INFO: ";
			break;

		case LogLevel::Warning:
			*m_ostream << "WARNING: ";
			break;

		case LogLevel::Error:
			*m_ostream << "ERROR: ";
			break;

		case LogLevel::Assert:
			*m_ostream << "ASSERT: ";
			break;

		}

		*m_ostream << getFileName(filename) << " (Line: " << line << ")\n";

		return true;
	}
}