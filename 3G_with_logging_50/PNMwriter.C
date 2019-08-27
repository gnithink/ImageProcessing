#include<PNMwriter.h>
#include<logging.h>


void PNMwriter::Write(char *filename)
{

    if(filename == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: output filename should be provided \n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    FILE *fptr = fopen(filename, "wb");
   
    fprintf(fptr, "P6\n %d  %d\n %d\n", image1->GetWidth(), image1->GetHeight(), image1->GetMaxval());
    
    fwrite(image1->GetPixel(), sizeof(unsigned char), 3*image1->GetHeight()*image1->GetWidth(), fptr);
    cout<<"Image Written to output\n";
    fclose(fptr);
    Logger::Finalize();
}

const char *PNMwriter::SinkName() {
    return "PNMwriter";
}