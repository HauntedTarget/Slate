#include "Logger.h"


namespace bls 
{
	bool Logger::Log(LogLevel logLevel, std::string filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case LogLevel::Info:
			*this << "INFO: ";
			break;

		case LogLevel::Warning:
			*this << "WARNING: ";
			break;

		case LogLevel::Error:
			*this << "ERROR: ";
			break;

		case LogLevel::Assert:
			*this << "ASSERT: ";
			break;

		}

		*this << getFileName(filename) << " (Line: " << line << ")\n";

		return true;
	}
}