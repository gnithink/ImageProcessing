#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);

    Rotate single_filter;
    Rotate r2;
    single_filter.SetInput(reader.GetOutput());
    r2.SetInput(single_filter.GetOutput());

    single_filter.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(single_filter.GetOutput());
    writer.Write(argv[2]);

    CheckSum cs;
    cs.SetInput(single_filter.GetOutput());
    cs.OutputCheckSum("rotate_checksum");
}
