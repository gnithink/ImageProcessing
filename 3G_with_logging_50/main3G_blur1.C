#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>

int main(int argc, char *argv[])
{
   // PNMreader reader(argv[1]);
    Color c1(100, 100, 255, 155, 55);
    Blur single_filter;

    single_filter.SetInput(c1.GetOutput());

    single_filter.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(single_filter.GetOutput());
    writer.Write(argv[2]);

    CheckSum cs;
    cs.SetInput(single_filter.GetOutput());
    cs.OutputCheckSum("blur_checksum");
}
