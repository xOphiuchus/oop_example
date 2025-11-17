#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger
{
public:
    static Logger &getInstance();
    void log(const std::string &message);
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

private:
    Logger();
    ~Logger();
    std::ofstream m_logFile;
    std::mutex m_mutex;
    static const std::string LOG_FILE;
};
