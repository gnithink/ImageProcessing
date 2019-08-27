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

#endif