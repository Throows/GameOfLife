#include "Logger.h"
#include <iostream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::setup(std::string fileName, std::string logName)
{
    try
    {
        this->m_consoleLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        this->m_consoleLogger->set_level(spdlog::level::info);

        this->m_fileLogger = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + fileName, true);
        this->m_fileLogger->set_level(spdlog::level::trace);

        spdlog::sinks_init_list sinkLists = { this->m_consoleLogger, this->m_fileLogger };
        this->logger = std::make_shared<spdlog::logger>(logName, sinkLists.begin(), sinkLists.end());
    }
    catch (const spdlog::spdlog_ex& ex) 
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}
