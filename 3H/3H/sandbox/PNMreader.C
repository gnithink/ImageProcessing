#include<PNMreader.h>
#include<string.h>
#include<logging.h>

void PNMreader::Execute()
{

    

    FILE *fptr = fopen(filename, "rb");

    int height = 0; int width = 0; int maxval = 0; char magic_num[128];
    if(fptr == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: input file is empty!\n", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    
    fscanf(fptr, "%s\n%d  %d \n %d\n ", magic_num, &width, &height, &maxval);
    if(strcmp(magic_num ,"P6") !=0)
    {
        char msg[128];
        sprintf(msg, "%s: The file is not of type PNM!\n", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    

    image.ResetSize(width, height);
    image.SetPixel();
    fread(image.GetPixel(), sizeof(unsigned char), 3*image.GetWidth()*image.GetHeight(), fptr);
    image.SetMaxval(maxval);
    fclose(fptr);
}
PNMreader::PNMreader()
{
    filename = NULL;
}
PNMreader::PNMreader(char *fname)
{   
    this->filename = new char[strlen(fname)+1];
    strcpy(filename,fname);
}

PNMreader::~PNMreader()
{
    if(filename != NULL)
        delete [] filename;
}

const char *PNMreader::SourceName() {
    return "PNMreader";
}

