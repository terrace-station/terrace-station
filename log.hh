#ifndef LOG_HH
#define LOG_HH

#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <time.h>

class Log
{
public:
    enum {ALL=0, DEBUG, INFO, WARNING, ERROR, CRITICAL, NONE};
    
    /**
     * Log to an arbitrary log-level
     * 
     * \param   level   the desired log-level
     * \param   fmt     format-string to be passed to vprintf
     */
    static void log(int level, const char *fmt, ...);
    
    /** Log to an the DEBUG log-level */
    static void debug(const char *fmt, ...);
    
    /** Log to an the INFO log-level */
    static void info(const char *fmt, ...);
    
    /** Log to an the WARNING log-level */
    static void warning(const char *fmt, ...);
    
    /** Log to an the ERROR log-level */
    static void error(const char *fmt, ...);
    
    /** Log to an the CRITICAL log-level */
    static void critical(const char *fmt, ...);
    
    /**
     * Initialize the logger
     * 
     * \param   stdout_level    log-level for logging to standard output
     * \param   log_file        path to logfile ("" means no logging to file)
     * \param   file_level      log-level for logging to logfile
     */
    static void init(int stdout_level=INFO, std::string log_file="", int file_level=DEBUG);

private:
    static void do_log(int level, const char *fmt, va_list args);
    static std::string get_timestamp(int level);
    static std::string get_level_name(int level);
    
    static int stdout_level;
    static std::string log_file;
    static int file_level;
};

#endif
