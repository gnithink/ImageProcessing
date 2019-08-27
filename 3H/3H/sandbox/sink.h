#include<image.h>
#ifndef SINK_H
#define SINK_H
class sink
{
    protected:
        const Image *image1;
        const Image *image2;
    
    public:
    void SetInput(const Image* img1);
    void SetInput2(const Image* img2);
    sink();
    virtual const char *SinkName() = 0;
};

class CheckSum : public sink
{
protected:
unsigned char r;
unsigned char g;
unsigned char b;
public:
void OutputCheckSum(const char *filename);
const char *SinkName();
};

#endif
