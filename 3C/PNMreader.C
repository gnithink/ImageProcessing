#include<PNMreader.h>
#include<string.h>
#include<image.h>

void PNMreader::Execute()
{
    FILE *fptr = fopen(filename, "rb");
    int height = 0; int width = 0; int maxval = 0; char magic_num[128];

    fscanf(fptr, "%s\n%d  %d \n %d\n ", magic_num, &width, &height, &maxval);
    
  //  unsigned char *pixel = new unsigned char(3*width*height);
    //cout<<"\n pixel memory allocated\n";
    

    image.ResetSize(width, height);
    image.SetPixel();
    fread(image.GetPixel(), sizeof(unsigned char), 3*image.GetWidth()*image.GetHeight(), fptr);
    cout<<"file read to pixel pointer \n";
    image.SetMaxval(maxval);
    cout<<"Image Read \n";
    fclose(fptr);
}
PNMreader::PNMreader()
{
    filename = NULL;
}
PNMreader::PNMreader(char *fname)
{   //this->filename = fname;
    this->filename = new char[sizeof(filename)+1];
    //this->filename = fname;
    strcpy(filename,fname);
    cout<<endl<<"input filename is "<<filename;
}

PNMreader::~PNMreader()
{
    if(filename != NULL)
        delete [] filename;
}