#include "log.hh"

#define OVERWRITE_LOGFILE true

int Log::stdout_level;
std::string Log::log_file;
int Log::file_level;

/**
 * Do the actual logging
 * 
 * This method is called by the other public log-methods.
 */
void Log::do_log(int level, const char *fmt, va_list args)
{
    if (level >= stdout_level || (log_file != "" && level >= file_level)) {
        if (level >= stdout_level) // log to stdout:
        {
            std::cout << get_timestamp(level);
            vprintf(fmt, args);
            std::cout << std::endl;
        }
        if (log_file != "" && level >= file_level) // log to file:
        {
            FILE* pFile;
            pFile = fopen(log_file.c_str(), "a");
                fprintf(pFile, "%s", get_timestamp(level).c_str());
                vfprintf(pFile, fmt, args);
                fprintf(pFile, "\n");
            fclose(pFile);
        }
    }
}

void Log::log(int level, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_log(level, fmt, args);
    va_end(args);
}

void Log::debug(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_log(Log::DEBUG, fmt, args);
    va_end(args);
}

void Log::info(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_log(Log::INFO, fmt, args);
    va_end(args);
}

void Log::warning(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_log(Log::WARNING, fmt, args);
    va_end(args);
}

void Log::error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_log(Log::ERROR, fmt, args);
    va_end(args);
}

void Log::critical(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_log(Log::CRITICAL, fmt, args);
    va_end(args);
}

std::string Log::get_timestamp(int level) {
    char buffer [40];
    char timestamp [80];
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%F %T", timeinfo);
    sprintf(timestamp, "%s %s> ", buffer, get_level_name(level).c_str());
    return std::string(timestamp);
}

std::string Log::get_level_name(int level) {
    switch(level) {
        case ALL:
            return "ALL"; break;
        case DEBUG:
            return "DEBUG"; break;
        case INFO:
            return "INFO"; break;
        case WARNING:
            return "WARNING"; break;
        case ERROR:
            return "ERROR"; break;
        case CRITICAL:
            return "CRITICAL"; break;
        case NONE:
            return "NONE"; break;
    }
}

void Log::init(int stdout_level, std::string log_file, int file_level)
{
    Log::stdout_level = stdout_level;
    Log::log_file = log_file;
    Log::file_level = file_level;
    if (log_file != "" && file_level < NONE && OVERWRITE_LOGFILE)
    {
        // clear logfile:
        FILE* pFile;
        pFile = fopen(log_file.c_str(), "w");
        fclose(pFile);
    }
}
