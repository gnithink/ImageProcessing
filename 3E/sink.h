#include<image.h>
#ifndef SINK_H
#define SINK_H
class sink
{
    protected:
        const Image *image1;
        const Image *image2;
    //Should simply point at images coming that come from sources
    public:
    void SetInput(const Image* img1);
    void SetInput2(const Image* img2);
    sink();
};

#endif
