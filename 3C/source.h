#include<image.h>

#ifndef Source_H
#define Source_H
class source
{
    protected:
        Image image;
    public:
        Image* GetOutput();
        void virtual Execute() = 0;
};

#endif