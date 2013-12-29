#ifndef LOG_HH
#define LOG_HH

#define LOG(level) \
if (level < Log::stdout_level && level < Log::file_level) ; \
else Log().log(level)

#include <iomanip>
#include <iostream>
#include <sstream>
#include <time.h>

enum LogLevel {ALL=0, DEBUG, INFO, WARNING, ERROR, CRITICAL, NONE, SIZE_OF_ENUM};
static const char* LogLevelNames[LogLevel::SIZE_OF_ENUM] = { "ALL", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL", "NONE" };

class Log
{
public:
    Log();
    virtual ~Log();
    
    /**
     * Log to an arbitrary log-level
     * 
     * \param   level   the desired log-level
     */
    std::ostringstream& log(LogLevel level);
    
    /**
     * Initialize the logger
     * 
     * \param   stdout_level    log-level for logging to standard output
     * \param   log_file        path to logfile ("" means no logging to file)
     * \param   file_level      log-level for logging to logfile
     * \param   replace_logfile overwrite old logfile
     */
    static void init(LogLevel stdout_level=WARNING, std::string log_file="", LogLevel file_level=WARNING, bool replace_logfile=true);
    
    /** the log-level for logging to stdout */
    static LogLevel stdout_level;
    
    /** the log-level for logging to the logfile */
    static LogLevel file_level;
    
protected:
    std::ostringstream logstream;
    
private:
    static std::string get_timestamp(LogLevel level);
    
    LogLevel message_level;
    static std::string log_file;
    static bool replace_logfile;
};

#endif
