#include<iostream>
#include<image.h>
#include<source.h>
#include <stdlib.h>
using namespace std;


Image::Image(){ //constructor
	pix = NULL;
	src = NULL;
	width = 0;
	height = 0;
	maxval = 0;
}

Image::Image(int h, int w, int max, unsigned char *pixel) //parameterized constructor
{
	width = w;
	height = h;
	maxval = max;
	pix = pixel;
}

Image::Image(const Image &img) //copy constructor
{
	height = img.height;
	width = img.width;
	maxval = img.maxval;
	
}

Image::~Image()
{
	if (pix != NULL)
	delete [] pix;
}

void Image::ResetSize(int w, int h)
{
	width = w;
	height = h;
	cout<<"\n"<<width<<"\n"<<height<<"\n";
}

void Image::SetMaxval(int max)
{
	maxval = max;
	cout<<"maxval set  "<<maxval<<"\n";
}

void Image::SetPixel()
{
	pix = new unsigned char[3*width*height];
	cout<<"Pixel set  "<<sizeof(pix)<<" bytes"<<"\n";
}

int Image::GetHeight() const
{
	return height;
}
int Image::GetWidth() const
{
	return width;
}

int Image::GetMaxval() const
{
	return maxval;
} 

unsigned char* Image::GetPixel() const
{
	return pix;
}

void Image::Update() const
{
	if (src != NULL) 
	{
        src->Update();
    }
}

void Image::setsource(source *s)
{
	src = s;
}

