#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>

int main(int argc, char *argv[])
{

    //Color c1(100, 100, 150, 200, 160);
    //Color c2(100, 100, 255, 155, 55);
    //Color c3(100, 200, 50, 50, 50);
    PNMreader reader(argv[1]);
    TBCombine tbcombine;
    tbcombine.SetInput(reader.GetOutput());
    tbcombine.SetInput2(reader.GetOutput());

    //Subtract single_filter;

    //single_filter.SetInput(lr.GetOutput());
    //single_filter.SetInput2(c3.GetOutput());

    tbcombine.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(tbcombine.GetOutput());
    writer.Write(argv[2]);

    /*CheckSum cs;
    cs.SetInput(tbcombine.GetOutput());
    cs.OutputCheckSum("subtract_checksum");*/
}
