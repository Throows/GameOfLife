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
            this->m_consoleLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            this->m_consoleLogger->set_level(spdlog::level::info);
            this->m_consoleLogger->set_pattern("[GameOfLife] [%^%l%$] %v");

            this->m_fileLogger = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + fileName, true);
            this->m_fileLogger->set_level(spdlog::level::trace);
            this->m_fileLogger->set_pattern("[GameOfLife] [%^%l%$] %v");

            spdlog::set_default_logger(std::make_shared<spdlog::logger>(logName, spdlog::sinks_init_list({this->m_consoleLogger, this->m_fileLogger})));
            spdlog::set_level(spdlog::level::trace);
        }
        catch (const spdlog::spdlog_ex& ex) 
        {
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
        spdlog::info("Logger created !");
    }
}