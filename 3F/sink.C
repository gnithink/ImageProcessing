#include<sink.h>
#include<image.h>

void sink::SetInput(const Image* img1)
{
this->image1 = img1;
}
void sink::SetInput2(const Image* img2)
{
this->image2 = img2;
}

sink::sink()
{
    image1 = NULL;
    image2 = NULL;
}