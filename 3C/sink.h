#include<image.h>
#ifndef SINK_H
#define SINK_H
class sink
{
    protected:
        Image *image1;
        Image *image2;
    //Should simply point at images coming that come from sources
    public:
    void SetInput(Image* img1);
    void SetInput2(Image* img2);
};

#endif
