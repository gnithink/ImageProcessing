#include<source.h>
#include<image.h>
#include<logging.h>

Image* source::GetOutput()
{
    return &image;
}

source::source()
{
    image.setsource(this);
}

void source::Update()
{
char msg[128];
sprintf(msg, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg);
Execute();
sprintf(msg, "%s: done executing \n", SourceName());
Logger::LogEvent(msg);
}

