#include "logger.hpp"

int Logger::id = 0;

Logger::Logger(const string& projName, string filePath)
{
	++id;
	if (id > 1) (throw "Можно объявить только один объект класса");
	if (projName.empty()) { throw "Название проекта не может быть пустым"; };
	if (filePath.empty()) { throw "Путь не может быть пустым"; };
	this->projName = projName;
	this->filePath = filePath;
	fileOpen();
	
}

Logger::Logger(const string& projName)
{
	++id;
	if (id > 1) (throw "Можно объявить только один объект класса");
	if (projName.empty()) { throw "Название проекта не может быть пустым"; };
	this->projName = projName;
	this->filePath = this->defaultFilePath;
	fileOpen();
}

void Logger::setPath(string filePath)
{
	if (filePath.empty()) throw "Путь не может быть пустым";
	this->filePath = filePath;

	if (fout.is_open()) fout.close();
	fileOpen();
}

Logger::~Logger()
{
	if (fout.is_open()) {
		fout.flush();
		fout.close();
	}
}

void Logger::fileOpen()
{
	try
	{
		fout.open(this->filePath, ofstream::app);
	}
	catch (const char* error)
	{
		cout << error << endl;
		terminate();
	};
}

std::string Logger::getCurrentTime()
{
	std::time_t currTime = std::time(nullptr);
	if (currTime == -1) return "TimeError";

	struct tm localTime;
	errno_t err = localtime_s(&localTime, &currTime);
	if (err) return "TimeError";

	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
	return std::string(buffer);
}

std::unordered_map<LogLevel, std::string> LogLevelToString{
	{LogLevel::Trace, "Trace"},
	{LogLevel::Debug, "Debug"},
	{LogLevel::Warning, "Warning"},
	{LogLevel::Information, "Information"},
	{LogLevel::Error, "Error"},
	{LogLevel::Critical, "Critical"},
	{LogLevel::Unknown, "UNKNOWN"},
};

const char* Logger::levelToString(LogLevel level)
{
	if (LogLevelToString.contains(level))
	{
		return LogLevelToString.at(level).c_str();
	}

	return LogLevelToString.at(LogLevel::Unknown).c_str();
}

/*template<LogLevel level>
void Logger::printLog(string message)
{
	lock_guard<mutex> lock(log_mutex); // блокировака потока
	string nowTime, nowDate = getCurrentTime();
	fout << "[" << nowDate << "] "
		<< "[" << nowTime << "] "
		<< "[" << this->projName << "] "
		<< "[" << levelToString(level) << "] "
		<< message << "\n";

	cout << "[" << nowDate << "] "
		<< "[" << nowTime << "] "
		<< "[" << this->projName << "] "
		<< "[" << levelToString(level) << "] "
		<< message << "\n";
}
*/