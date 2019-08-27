#include<iostream>
#ifndef IMAGE_H
#define IMAGE_H
using namespace std;
class source;
class Image{
	private:
		unsigned char *pix;
		source *src;
		int height;
		int width;
		int maxval;
		
	public:
		Image();
		Image(int height, int width, int max, unsigned char *pix);
		Image(const Image &img);
		virtual ~Image();
		void ResetSize(int width, int height) ;
		void SetPixel() ;
		void SetMaxval(int maxval) ;
		void setsource(source *s);
		
		int GetHeight() const ;
		int GetWidth() const;
		int GetMaxval() const ;
		unsigned char* GetPixel() const; 
		void Update() const;
		

};

#endif

