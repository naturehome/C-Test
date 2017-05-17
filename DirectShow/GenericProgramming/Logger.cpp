
#include <stdexcept>
#include "Logger.h"
#include <stdio.h>

const std::string Logger::KLogLevelDebug = "DEBUG";
const std::string Logger::KLogLevelInfo = "INFO";
const std::string Logger::KLogLevelError = "ERROR";
const char* const Logger::KlogFileName = "log.txt";
Logger* Logger::pInstance = nullptr;
std::mutex Logger::sMutex;

Logger::Logger()
{
	sOutputStream.open(KlogFileName, std::ios::app);
	if (!sOutputStream.good())
	{
		throw std::runtime_error("Unable to initialized the Logger");
	}
}


Logger::~Logger()
{
	sOutputStream.close();
}

Logger& Logger::instance()
{
	static CleanUp cleanup;
	std::lock_guard<std::mutex> guard(sMutex);
	if (pInstance == nullptr)
		pInstance = new Logger();
	return *pInstance;
}

Logger::CleanUp::~CleanUp()
{
	std::lock_guard<std::mutex> guard(Logger::sMutex);
	delete Logger::pInstance;
	Logger::pInstance = nullptr;
}

void Logger::log(const std::string& inMessage, const std::string& inLogLevel)
{
	std::lock_guard<std::mutex> guard(sMutex);
	LogHelper(inMessage, inLogLevel);
}

void Logger::LogHelper(const std::string& inMessage, const std::string& inLogLevel)
{
	sOutputStream << inLogLevel << ":" << inMessage << std::endl;
}

void Logger::log(const std::string& inLogLevel, ...)
{	
	
}