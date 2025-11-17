#include "Logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

const std::string Logger::LOG_FILE = "task_manager.log";

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    m_logFile.open(LOG_FILE, std::ios::out | std::ios::app);
    if (!m_logFile.is_open())
    {
        std::cerr << "Error: Could not open log file." << std::endl;
    }
    log("--- Logger Initialized ---");
}

Logger::~Logger()
{
    log("--- Logger Shutdown ---");
    if (m_logFile.is_open())
    {
        m_logFile.close();
    }
}

void Logger::log(const std::string &message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    m_logFile << "[" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << "] "
              << message << std::endl;
}
