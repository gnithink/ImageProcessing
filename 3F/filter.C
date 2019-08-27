//#include<image.h>
#include<filter.h>
#include<source.h>
#include<sink.h>
#include<logging.h>

void filter::Update()
{   char msg[128];
    if(image1 !=NULL)
    {   sprintf(msg, "%s: about to update input1\n", FilterName());
        Logger::LogEvent(msg);
        image1->Update();
        sprintf(msg, "%s: done updating input1 \n", FilterName());
        Logger::LogEvent(msg);
        
    }
    if(image2 !=NULL)
    {
        sprintf(msg, "%s: about to update input2\n", FilterName());
        Logger::LogEvent(msg);
        image2->Update();
        sprintf(msg, "%s: done updating input2\n", FilterName());
        Logger::LogEvent(msg);
        
    }
    sprintf(msg, "%s: about to execute\n", FilterName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing\n", FilterName());
    Logger::LogEvent(msg);

}

const char *Shrinker::FilterName()
{
    return "Shrinker";
}

const char *LRCombine::FilterName()
{
    return "LRConcat";
}
const char *TBCombine::FilterName()
{
    return "TBconcat";
}
const char *Blender::FilterName()
{
    return "Blender";
}

const char *filter::SourceName()
{
    return FilterName();
}

const char *filter::SinkName()
{
    return FilterName();
}

void Shrinker::Execute()
{   
    if (image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1", SinkName());
        DataFlowException e(SinkName(), msg);
    }
    int out_width = image1->GetWidth()/2;
    int out_height = image1->GetHeight()/2;

    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    cout<<"\n"<<"Getting values  "<<image1->GetWidth()<<"\n"<<image1->GetHeight();

    for (int i = 0; i< image.GetHeight(); i++)
    {
        for (int j = 0; j< image.GetWidth(); j++)
        {   int position_shrinker= 3*(i*image.GetWidth() + j);
            int position_input = 3* (i*image1->GetWidth()*2 + 2*j );
            image.GetPixel()[position_shrinker] =image1->GetPixel()[position_input];
            image.GetPixel()[position_shrinker + 1] =image1->GetPixel()[position_input +1];
            image.GetPixel()[position_shrinker + 2] =image1->GetPixel()[position_input + 2];
        }
    }
  cout<<"\n"<<"Getting values  "<<image1->GetWidth()<<"\n"<<image1->GetHeight();
}

void LRCombine::Execute()
{   
    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    printf("%s: no input1!\n", SinkName());
    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
             throw e;
    }
    
    if (image1->GetHeight() != image2->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d\n", SinkName(), image1->GetHeight(),image2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    

    int out_height = 0;
    if(image1->GetHeight() > image2->GetHeight())
    {
        out_height = image1->GetHeight();
    }
    else
    {
        out_height = image2->GetHeight();
    }
    int out_width = image1->GetWidth() + image2->GetWidth();
    

    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    for (int i =0; i< image.GetHeight(); i++)
    {
        for(int j=0; j< image.GetWidth(); j++)
        {
            int position = 3*(i*image.GetWidth()+j);
            if(j<image1->GetWidth())
            {   
                int position_left = 3*(i*image1->GetWidth()+j);
                image.GetPixel()[position] = image1->GetPixel()[position_left];
                image.GetPixel()[position+1] = image1->GetPixel()[position_left+1];
                image.GetPixel()[position+2] = image1->GetPixel()[position_left+2];
            }
            else
            {   int position_right = 3*(i*image2->GetWidth()+j);
                image.GetPixel()[position] = image2->GetPixel()[position_right];
                image.GetPixel()[position+1] = image2->GetPixel()[position_right+1];
                image.GetPixel()[position+2] = image2->GetPixel()[position_right+2];
            }

        }
    }
    
}

void TBCombine::Execute()
{
    if (image1 == NULL) {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    printf("%s: no input1!", SinkName());

    if (image2 == NULL) {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if (image1->GetWidth() != image2->GetWidth()) {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), image1->GetWidth(), image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = 0;
    if(image1->GetWidth() > image2->GetWidth())
    {
        out_width = image1->GetWidth();
    }
    else
    {
        out_width = image2->GetWidth();
    }
    int out_height = image2->GetHeight() + image1->GetHeight();
    

    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    for (int i =0; i< image1->GetHeight(); i++)
    {
        for(int j=0; j< image.GetWidth(); j++)
        {
            int position = 3*(i*image.GetWidth()+j);
            
               
            int position_upper = 3*(i*image.GetWidth()+j);
            image.GetPixel()[position] = image1->GetPixel()[position_upper];
            image.GetPixel()[position+1] = image1->GetPixel()[position_upper+1];
            image.GetPixel()[position+2] = image1->GetPixel()[position_upper+2];
        }
    }
    for (int i =0; i< image2->GetHeight(); i++)
    {
        for(int j=0; j< image.GetWidth(); j++)
        {
                int position = 3*image1->GetHeight()*image1->GetWidth() + 3*(i*image.GetWidth()+j);
                int position_lower = 3*(i*image2->GetWidth()+j);
                image.GetPixel()[position] = image2->GetPixel()[position_lower];
                image.GetPixel()[position+1] = image2->GetPixel()[position_lower+1];
                image.GetPixel()[position+2] = image2->GetPixel()[position_lower+2];
        }
    }
}

void Blender::Execute()
{
    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    printf("%s: no input1!\n", SinkName());
    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if (factor < 0 || factor > 1)
    {
        char msg[1024];
        sprintf(msg, "%s: factor is invalid: %f\n", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = 0;
    int out_height = 0;
/*
    if(image1->GetWidth()>image2->GetWidth())
        out_width = image1->GetWidth();
    else
        out_width = image2->GetWidth();

    if(image1->GetHeight()>image2->GetHeight())
        out_height = image1->GetHeight();
    else
        out_height = image2->GetHeight();
     */   
    if (image1->GetWidth() != image2->GetWidth() || image1->GetHeight() != image2->GetHeight()) 
    {
        char msg[1024];
        sprintf(msg, "%s: image sizes must hatch: %d x %d, %d x %d", SinkName(), image1->GetWidth(), image1->GetHeight(), image2->GetWidth(), image2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    out_height = image1->GetHeight();
    out_width = image1->GetWidth();
    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);

    for (int i = 0; i< image.GetHeight(); i++)
    {
        for (int j = 0; j< image.GetWidth(); j++)
        {      int position = 3* (i*image.GetWidth()+j);
                int i1_position = 3*(i*image1->GetWidth()+j);
                int i2_position = 3*(i*image2->GetWidth()+j);
            image.GetPixel()[position] =factor*image1->GetPixel()[i1_position] + (1-factor)*image2->GetPixel()[i2_position];
            image.GetPixel()[position+1] =factor*image1->GetPixel()[i1_position+1] + (1-factor)*image2->GetPixel()[i2_position+1];
            image.GetPixel()[position+2] =factor*image1->GetPixel()[i1_position+2] + (1-factor)*image2->GetPixel()[i2_position+2];
        }
    }
}

void Blender::SetFactor(float fact)
{
    factor = fact;
}