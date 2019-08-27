#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
unsigned char *pix;
int height;
int width;
} Image;

Image *
ReadImage(char *filename)
{
  FILE *f_in;
  Image *i;
  char magicNum[128];
  int width, height, maxval;
  i = malloc(sizeof(Image));
  f_in = fopen(filename, "rb");
  fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
 // printf("%s\n %d \n %d\n %d\n", magicNum, width, height, maxval);
  i->height = height;
  i->width = width; 
  i->pix = malloc(sizeof(unsigned char)*3*i->height*i->width);
  fread(i->pix,sizeof(unsigned char),3*i->width*i->height,f_in);
//  printf("%s\n %d \n %d\n %d\n", magicNum, width, height, maxval);
  fclose(f_in);
  return i;
}


void WriteImage(Image *img, char *filename)
{
FILE *fptr =fopen(filename, "wb");
fprintf(fptr, "P6\n%d\n %d\n255\n", img->width, img->height);
fwrite(img->pix, sizeof(unsigned char), 3*img->width*img->height, fptr);
fclose(fptr);

}


Image *
YellowDiagonal(Image *input)
{
Image *yellow;
int i;
int j;
yellow = malloc(sizeof(Image));
yellow->height = input->height;
yellow->width = input->width;
yellow->pix = malloc(sizeof(unsigned char)*3*yellow->height*yellow->width);
memmove(yellow->pix, input->pix, sizeof(unsigned char)*3*yellow->height*yellow->width);
printf(" %d \n %d", yellow->width,yellow->height);
for ( i = 0; i<=yellow->width; i++)
{
yellow->pix[3*(yellow->width*i+i) + 0] = 255;
yellow->pix[3*(yellow->width*i+i) + 1] = 255;
yellow->pix[3*(yellow->width*i+i) + 2] = 0;
}
return yellow;

}

int main(int argc, char *argv[])
{  
   Image *store;
   Image *yellow;
   char *input = argv[1];
   char *output = argv[2];
   store = ReadImage(input);
   printf(" %d \n %d", store->width,store->height);
   yellow = YellowDiagonal(store);
   WriteImage(yellow, output);  
   free(store);
   free(yellow);
   return 0;
  
}
