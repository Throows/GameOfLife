#include "Logger.h"
#include <iostream>
namespace GOL 
{

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
            auto cLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            this->m_consoleLogger = std::move(cLogger);
            this->m_consoleLogger->set_level(spdlog::level::info);
            this->m_consoleLogger->set_pattern("[GameOfLife] [%^%l%$] %v");

            auto fLogger = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + fileName, true);
            this->m_fileLogger = std::move(fLogger);
            this->m_fileLogger->set_level(spdlog::level::trace);
            this->m_fileLogger->set_pattern("[GameOfLife] [%^%l%$] %v");

            spdlog::sinks_init_list sinkLists = { this->m_consoleLogger, this->m_fileLogger };
            this->logger = std::make_shared<spdlog::logger>(logName, sinkLists.begin(), sinkLists.end());
            this->logger->set_level(spdlog::level::trace);
        }
        catch (const spdlog::spdlog_ex& ex) 
        {
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
        logger->info("Logger created !");
    }
}