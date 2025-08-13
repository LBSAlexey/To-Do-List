#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <mutex>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <sstream>


enum class LogLevel : std::uint8_t
{
    Trace = 0,      // ��������� �����������
    Debug = 1,      // ���������� ����������
    Information = 2,// ������� ��������
    Warning = 3,    // ��������������
    Error = 4,      // ������ ����������
    Critical = 5,    // ����������� ����
    Unknown = 6
};
/*
std::unordered_map<LogLevel, std::string> LogLevelToString{
    {LogLevel::Trace, "Trace"},
    {LogLevel::Debug, "Debug"},
    {LogLevel::Warning, "Warning"},
    {LogLevel::Information, "Information"},
    {LogLevel::Error, "Error"},
    {LogLevel::Critical, "Critical"},
    {LogLevel::Unknown, "UNKNOWN"},
};
*/

class Logger
{
    std::mutex log_mutex{}; // ��� ����������������
    std::ofstream fout{}; // ������ �����

    static inline const  std::string defaultFilePath = "logger.txt";
    static int id;
    
public:

    Logger(const  std::string& projName); // ����������� 1 - �������� �������
    Logger(const  std::string& projName,  std::string filePath = "logger.txt");
    // ����������� 1 - �������� �������, 2 - ���� � ������

    void setPath( std::string filePath);

    template<LogLevel level> 
    void printLog( std::string message)
        {
             std::lock_guard< std::mutex> lock(log_mutex);
             std::string datetime = getCurrentTime();  // ����������: ���� ���������� ��� ���� � �������

            fout << "[" << datetime << "] "
                << "[" << this->projName << "] "
                << "[" << levelToString(level) << "] "
                << message << "\n";

            // cout << "[" << datetime << "] "
            //     << "[" << this->projName << "] "
            //     << "[" << levelToString(level) << "] "
            //     << message << "\n";
        };
        
    ~Logger();
private: 
    
    void fileOpen();
     std::string getCurrentTime();
    const char* levelToString(LogLevel level);
     std::string filePath{};
     std::string projName{};
};

#endif //LOGGER_H