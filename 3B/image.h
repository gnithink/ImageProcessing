#include<iostream>
#ifndef IMAGE_H
#define IMAGE_H
using namespace std;

class Image{
	private:
		unsigned char *pix;
		int height;
		int width;
		int maxval;
		
	public:
		Image();
		Image(int height, int width, int max, unsigned char *pix);
		Image(const Image &img);
		~Image();
		void ResetSize(int width, int height);
		void SetPixel();
		void SetMaxval(int maxval);
		
		int GetHeight();
		int GetWidth();
		int GetMaxval();
		unsigned char* GetPixel();

};

#endif

