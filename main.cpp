#include <iostream>
#include "MyLog/Config.h"
#include "common.h"
#include <stdarg.h>
#include <iostream>
#include <string>
#include <memory>
#include <map>

using namespace std;
namespace MyLog
{
    enum LogLevel
    {
        DEBUG=90,
        WARN = 33,
        INFO = 32,
        ERROR = 31,
        FATAL = 35
    };

    class Logger
    {
    public:
        Logger(const std::string & source):mSource(source) {}
        template<typename... Args>
        void warn(const std::string & message, Args&&... args)
        {
            log(std::move(string_format(message,args...)),"WARN",LogLevel::WARN);
        }

        template<typename... Args>
        void info(const std::string & message, Args&&... args)
        {
            log(std::move(string_format(message,args...)),"INFO", LogLevel::INFO);
        }

        template<typename... Args>
        void debug(const std::string & message, Args&&... args)
        {
            log(std::move(string_format(message,args...)),"DEBUG", LogLevel::DEBUG);
        }

        template<typename... Args>
        void error(const std::string & message, Args&&... args)
        {
            log(std::move(string_format(message,args...)),"ERROR", LogLevel::ERROR);
        }

        template<typename... Args>
        void fatal(const std::string & message, Args&&... args)
        {
            log(std::move(string_format(message ,args...)),"FATAL",LogLevel::FATAL);
        }

    private:

        inline void log(const std::string & message, const std::string logName, LogLevel logLevel)
        {
            std::cout << "\033[0;" << logLevel << "m" << "["<< mSource <<"] ["<< logName << "] " << message << "\033[0m" <<endl;
        }

        template<typename... Args>
        string string_format( const std::string& format, Args&&...  args )
        {
            size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
            std::unique_ptr<char[]> buf( new char[ size ] );
            snprintf( buf.get(), size, format.c_str(), args ... );
            return std::move(string( buf.get(), buf.get() + size - 1 ));
        }

    private:
        std::string mSource;
    };
}


int main() {
    MyLog::Logger logger("main");
    logger.debug("Test int type: %d" ,5);
    logger.warn("Test string type: %s" ," this is test");
    logger.info("Test float data type: %f" ,5.4);
    logger.error("test  %.1f" ,5.3);
    logger.fatal("test %d" ,5);

    return 0;
}