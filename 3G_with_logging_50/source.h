#include<image.h>

#ifndef Source_H
#define Source_H
class source
{
    protected:
        Image image;
        virtual void Execute() = 0;
    public:
        Image* GetOutput();
        virtual void Update();
        source();
        virtual const char *SourceName() = 0;
};

class Color : public source
{
protected:
    int height;
    int width;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
public:
    Color(int w, int h, unsigned char r, unsigned char g, unsigned char b);
    virtual void Execute();
    virtual const char *SourceName();
};
#endif