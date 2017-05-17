#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <mutex>

class Logger /*:public std::enable_shared_from_this<Logger>*/
{
public:
	static const std::string KLogLevelDebug;
	static const std::string KLogLevelInfo;
	static const std::string KLogLevelError;

	static Logger& instance();
	void log(const std::string& inMessage, const std::string& inLogLevel);
	void log(const std::string& inLogLevel, ...);
protected:
	friend class CleanUp;
	static Logger* pInstance;
	static const char* const KlogFileName;
	std::ofstream sOutputStream;

	
	class CleanUp
	{
	public:
		~CleanUp();
	};

	void LogHelper(const std::string& inMessage, const std::string& inLogLevel);
private:
	Logger();
	virtual ~Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);

	static std::mutex sMutex;
};

