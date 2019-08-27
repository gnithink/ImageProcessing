#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);
    //Color c1(30,30, 255,155,55);
    Rotate single_filter;
    Rotate r2;
    Rotate r3;
    Rotate r4;
    Rotate r5;
    Rotate r6;

    single_filter.SetInput(reader.GetOutput());
    r2.SetInput(single_filter.GetOutput());
    r3.SetInput(r2.GetOutput());
    r4.SetInput(r3.GetOutput());
    r5.SetInput(r4.GetOutput());
    r6.SetInput(r5.GetOutput());
    
    r6.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(r3.GetOutput());
    writer.Write(argv[2]);

    CheckSum cs;
    cs.SetInput(single_filter.GetOutput());
    cs.OutputCheckSum("rotate_checksum");
}
