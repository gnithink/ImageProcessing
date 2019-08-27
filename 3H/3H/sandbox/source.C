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

Color::Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
}

void Color::Execute()
{
    if ( red < 0 || red > 255) {
        char msg[128];
        sprintf(msg, "%s: red value should be between 0 and 255: %u", SourceName(), red);
        DataFlowException e(SourceName(), msg);
        throw e;
    }

    if ( green < 0 || green > 255) {
        char msg[128];
        sprintf(msg, "%s: blue value should be between 0 and 255: %u", SourceName(), green);
        DataFlowException e(SourceName(), msg);
        throw e;
    }

    if ( blue < 0 || blue > 255) {
        char msg[128];
        sprintf(msg, "%s: invalid blue value (0-255): %u", SourceName(), blue);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    image.ResetSize(width, height);
    image.SetPixel();
    image.SetMaxval(255);

    for(int i =0; i<image.GetHeight(); i++)
    {
        for (int j=0; j<image.GetWidth(); j++)
        {
            int position = 3*(i*image.GetWidth() + j);
            image.GetPixel()[position] = red;
            image.GetPixel()[position + 1] = green;
            image.GetPixel()[position + 2] = blue;
        }
    }
}

const char *Color::SourceName()    
{ 
    return "Color"; 
    }
