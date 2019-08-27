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

void CheckSum::OutputCheckSum(const char *filename)
{    //cout<<image1->GetWidth();
    FILE *fptr = fopen(filename, "w");
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    for(int i = 0; i < image1->GetHeight(); i++)
	{
		for(int j = 0; j < image1->GetWidth(); j++)
		{
            int position = 3*(i*image1->GetWidth()+j);
            r += image1->GetPixel()[position];
            g += image1->GetPixel()[position+1];
            b += image1->GetPixel()[position+2];
        }
    }
    fprintf(fptr, "CHECKSUM: %u, %u, %u\n", r, g, b);
    fclose(fptr);

}

const char *CheckSum::SinkName()  
{ 
    return "CheckSum"; 
    }