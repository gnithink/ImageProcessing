#include<PNMwriter.h>


void PNMwriter::Write(char *filename)
{
    FILE *fptr = fopen(filename, "wb");
    cout<<"new file opened \n";
    cout<<"\n"<<"Getting values  "<<image1->GetWidth()<<"\n"<<image1->GetHeight();
    fprintf(fptr, "P6\n %d  %d\n %d\n", image1->GetWidth(), image1->GetHeight(), image1->GetMaxval());
    cout<<"written image values to output \n";
    cout<<"\n"<<image1->GetWidth()<< "  "<<image1->GetHeight()<<"\n";
    cout<<"\n"<<"Getting values  "<<image1->GetWidth()<<"\n"<<image1->GetHeight();
    fwrite(image1->GetPixel(), sizeof(unsigned char), 3*image1->GetHeight()*image1->GetWidth(), fptr);
    cout<<"Image Written to output\n";
    fclose(fptr);
}
