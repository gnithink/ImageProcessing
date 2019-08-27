#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <logging.h>
#include <iostream>
using std::cerr;
using std::endl;


void Execution1(char *filename)
{
    PNMreader reader(filename);
    PNMwriter writer;
    Shrinker shrinker1;
    Shrinker shrinker2;
    LRCombine lrcombine1;
    LRCombine lrcombine2;
    TBCombine tbcombine1;
    TBCombine tbcombine2;
    Blender  blender;
    blender.SetFactor(0.8);

    shrinker1.SetInput(reader.GetOutput());

    lrcombine1.SetInput(shrinker1.GetOutput());
    lrcombine1.SetInput2(reader.GetOutput());

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine1.GetOutput());

    shrinker2.SetInput(tbcombine1.GetOutput());

    lrcombine2.SetInput(shrinker2.GetOutput());

    tbcombine2.SetInput(lrcombine2.GetOutput());
    tbcombine2.SetInput2(lrcombine1.GetOutput());

    blender.SetInput(tbcombine2.GetOutput());
    blender.SetInput2(reader.GetOutput());

    writer.SetInput(blender.GetOutput());

    bool noException = true;
    try
    {
        blender.GetOutput()->Update();
    }
    catch (DataFlowException &)
    {
        Logger::LogEvent("Caught exception in Execution1!\n");
        noException = false;
    }
    if (noException)
    {
        Logger::LogEvent("No exception for Execution1!\n");
    }
 
}

void Execution2(char *filename)
{
    PNMreader reader(filename);
    PNMwriter writer;
    Shrinker shrinker1;
    Shrinker shrinker2;
    LRCombine lrcombine1;
    LRCombine lrcombine2;
    TBCombine tbcombine1;
    TBCombine tbcombine2;
    Blender  blender;
    blender.SetFactor(0.8);

    shrinker1.SetInput(reader.GetOutput());

    lrcombine1.SetInput(shrinker1.GetOutput());
    lrcombine1.SetInput2(shrinker1.GetOutput());

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine1.GetOutput());

    shrinker2.SetInput(tbcombine1.GetOutput());

    lrcombine2.SetInput(shrinker2.GetOutput());

    tbcombine2.SetInput(lrcombine2.GetOutput());

    blender.SetInput(tbcombine2.GetOutput());
    blender.SetInput2(reader.GetOutput());

    writer.SetInput(blender.GetOutput());


    bool noException = true;
    try
    {
        blender.GetOutput()->Update();
    }
    catch (DataFlowException &)
    {
        Logger::LogEvent("Caught exception in Execution2!\n");
        noException = false;
    }
    if (noException)
    {
        Logger::LogEvent("No exception for Execution2!\n");
    }
    
}

void Execution3(char *filename)
{
    PNMreader reader(filename);
    PNMwriter writer;
    Shrinker shrinker1;
    Shrinker shrinker2;
    LRCombine lrcombine1;
    LRCombine lrcombine2;
    TBCombine tbcombine1;
    TBCombine tbcombine2;
    Blender  blender;
    blender.SetFactor(1.2);

    shrinker1.SetInput(reader.GetOutput());

    lrcombine1.SetInput(shrinker1.GetOutput());
    lrcombine1.SetInput2(shrinker1.GetOutput());

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine1.GetOutput());

    shrinker2.SetInput(tbcombine1.GetOutput());

    lrcombine2.SetInput(shrinker2.GetOutput());
    lrcombine2.SetInput2(shrinker1.GetOutput());

    tbcombine2.SetInput(lrcombine2.GetOutput());
    tbcombine2.SetInput2(lrcombine1.GetOutput());

    blender.SetInput(tbcombine2.GetOutput());
    blender.SetInput2(reader.GetOutput());

    writer.SetInput(blender.GetOutput());


    bool noException = true;
    try
    {
        blender.GetOutput()->Update();
    }
    catch (DataFlowException &)
    {
        Logger::LogEvent("Caught exception in Execution3!\n");
        noException = false;
    }
    if (noException)
    {
        Logger::LogEvent("No exception for Execution3!\n");
    }
    
    
}

void Execution4(char *filename)
{
    PNMreader reader(filename);
    PNMwriter writer;
    Shrinker shrinker1;
    Shrinker shrinker2;
    LRCombine lrcombine1;
    LRCombine lrcombine2;
    TBCombine tbcombine1;
    TBCombine tbcombine2;
    Blender  blender;
    blender.SetFactor(0.8);

    shrinker1.SetInput(reader.GetOutput());

    lrcombine1.SetInput(shrinker1.GetOutput());
    lrcombine1.SetInput2(shrinker1.GetOutput());

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine1.GetOutput());

    shrinker2.SetInput(tbcombine1.GetOutput());

    lrcombine2.SetInput(shrinker2.GetOutput());
    lrcombine2.SetInput2(shrinker1.GetOutput());

    tbcombine2.SetInput(lrcombine2.GetOutput());
    tbcombine2.SetInput2(lrcombine1.GetOutput());

    blender.SetInput(tbcombine2.GetOutput());
    blender.SetInput2(reader.GetOutput());

    writer.SetInput(blender.GetOutput());

    bool noException = true;
    try
    {
        blender.GetOutput()->Update();
    }
    catch (DataFlowException &)
    {
        Logger::LogEvent("Caught exception in Execution4!");
        noException = false;
    }
    if (noException)
    {
        Logger::LogEvent("No exception for Execution4!");
    }

}

int main(int argc, char *argv[])
{/*
   Logger::LogEvent("Begin execution 1\n");
    Execution1(argv[1]);
    Logger::LogEvent("Done with execution 1\n");

    Logger::LogEvent("Begin execution 2\n");
    Execution2(argv[1]);
    Logger::LogEvent("Done with execution 2\n");

    Logger::LogEvent("Begin execution 3\n");
    Execution3(argv[1]);
    Logger::LogEvent("Done with execution 3\n");
*/
    Logger::LogEvent("Begin execution 4 \n");
    Execution4(argv[1]);
    Logger::LogEvent("Done with execution 4 \n");
  

    Logger::Finalize();
}
