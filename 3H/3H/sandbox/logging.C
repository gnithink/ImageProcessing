#include<logging.h>
#include<string.h>

FILE *Logger::logger = fopen("logger.txt", "wb");



void Logger::LogEvent(const char *event)
{
    fwrite(event, sizeof(char), strlen(event), logger);
}

void Logger::Finalize()
{
    fclose(logger);
}

DataFlowException::DataFlowException(const char *type, const char *error)
{
    sprintf(msg, "Throwing Exception: (%s): %s", type, error);
    Logger::LogEvent(msg);
}