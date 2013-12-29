#include "log.hh"

LogLevel Log::stdout_level;
std::string Log::log_file;
LogLevel Log::file_level;
bool Log::replace_logfile;

std::ostringstream& Log::log(LogLevel level)
{
    logstream << get_timestamp(level) << '\t' << std::string(level >= WARNING ? 0 : 2 * (WARNING - level), ' ');
    message_level = level;
    return logstream;
}

Log::Log() {}

Log::~Log()
{
    logstream << std::endl;
    if (message_level >= stdout_level)
    {
        fprintf(stdout, "%s", logstream.str().c_str());
        fflush(stdout);
    }
    if (log_file != "" && message_level >= file_level)
    {
        FILE* pFile;
        pFile = fopen(log_file.c_str(), "a");
            fprintf(pFile, "%s", logstream.str().c_str());
        fclose(pFile);
    }
}

std::string Log::get_timestamp(LogLevel level) {
    char buffer [40];
    char timestamp [80];
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%F %T", timeinfo);
    sprintf(timestamp, "%s %s> ", buffer, LogLevelNames[level]);
    return std::string(timestamp);
}

void Log::init(LogLevel stdout_level, std::string log_file, LogLevel file_level, bool replace_logfile)
{
    Log::stdout_level = stdout_level;
    Log::log_file = log_file;
    Log::file_level = file_level;
    if (log_file != "" && file_level < NONE && replace_logfile)
    {
        // clear logfile:
        FILE* pFile;
        pFile = fopen(log_file.c_str(), "w");
        fclose(pFile);
    }
}
