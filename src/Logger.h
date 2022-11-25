#pragma once 

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

typedef std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> ConsoleLogger;
typedef std::shared_ptr<spdlog::sinks::basic_file_sink_mt> FileLogger;

namespace GOL 
{
    class Logger
    {
    public:
        Logger();
        ~Logger();

        void setup(std::string fileName, std::string logName);

        std::shared_ptr<spdlog::logger> logger = spdlog::default_logger();

    private:
        ConsoleLogger m_consoleLogger;
        FileLogger m_fileLogger;
    };

}