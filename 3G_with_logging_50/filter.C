#include<filter.h>
#include<logging.h>


int counter = 0;
int limit = 1000;


void filter::Update()
{   char msg[128];
    counter++;
    if (counter > limit)
    {
        sprintf(msg, "%s: Update limit of iterations reached \n", FilterName());
        Logger::LogEvent(msg);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
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

const char *Subtract::FilterName()
{
    return "Subtract";
}
const char *Mirror::FilterName()
{
    return "Mirror";
}

const char *Rotate::FilterName()
{
    return "Rotate";
}
const char *Grayscale::FilterName()
{
    return "Grayscale";
}

const char *Blur::FilterName()
{
    return "Blur";
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
        char msg[128];
        sprintf(msg, "%s: no input1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = image1->GetWidth()/2;
    int out_height = image1->GetHeight()/2;

    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    

    for (int i = 0; i< image.GetHeight(); i++)
    {
        for (int j = 0; j< image.GetWidth(); j++)
        {   int position_shrinker= 3*(i*image.GetWidth() + j);
            int position_input = 3* (i*image1->GetWidth()*2 + 2*j);
            image.GetPixel()[position_shrinker] =image1->GetPixel()[position_input];
            image.GetPixel()[position_shrinker + 1] =image1->GetPixel()[position_input +1];
            image.GetPixel()[position_shrinker + 2] =image1->GetPixel()[position_input + 2];
        }
    }
  
}

void LRCombine::Execute()
{   
    if(image1 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(image2 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
             throw e;
    }
    
    if (image1->GetHeight() != image2->GetHeight())
    {
        char msg[128];
        sprintf(msg, "%s: heights must match: %d, %d\n", SinkName(), image1->GetHeight(),image2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int out_width = image1->GetWidth() + image2->GetWidth();
    int out_height = image1->GetHeight();
    

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
            {   int position_right = 3*(i*image2->GetWidth()+j - image1->GetWidth());
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
        char msg[128];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    

    if (image2 == NULL) {
        char msg[128];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if (image1->GetWidth() != image2->GetWidth()) {
        char msg[128];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), image1->GetWidth(), image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = image1->GetWidth();
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
        char msg[128];
        sprintf(msg, "%s: no input1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(image2 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if (factor < 0 || factor > 1)
    {
        char msg[128];
        sprintf(msg, "%s: factor is invalid: %f\n", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = 0;
    int out_height = 0;

    if (image1->GetWidth() != image2->GetWidth() || image1->GetHeight() != image2->GetHeight()) 
    {
        char msg[128];
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

void Subtract::Execute()
{
    
    if(image1 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(image2 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
             throw e;
    }
    
    if (image1->GetHeight() != image2->GetHeight())
    {
        char msg[128];
        sprintf(msg, "%s: heights must match: %d, %d\n", SinkName(), image1->GetHeight(),image2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if (image1->GetWidth() != image2->GetWidth())
    {
        char msg[128];
        sprintf(msg, "%s: widths must match: %d, %d\n", SinkName(), image1->GetWidth(),image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
        int out_width = 0;
        int out_height = 0;
        out_width = image1->GetWidth();
        out_height = image1->GetHeight();
        image.ResetSize(out_width, out_height);
        image.SetPixel();
        image.SetMaxval(255);
        for(int i=0; i< image.GetHeight(); i++)
        {
            for(int j=0; j< image.GetWidth(); j++)
            {
                int position_subtract = 3*(i*image.GetWidth()+j);
                int position_input = 3*(i*image.GetWidth() + j);
                if(image1->GetPixel()[position_input+2] > image2->GetPixel()[position_input+2])
                    image.GetPixel()[position_subtract+2] = image1->GetPixel()[position_input+2] - image2->GetPixel()[position_input+2];
                else
                    image.GetPixel()[position_subtract+2] = 0;
                if(image1->GetPixel()[position_input+1] > image2->GetPixel()[position_input+1])
                    image.GetPixel()[position_subtract+1] = image1->GetPixel()[position_input+1] - image2->GetPixel()[position_input+1];
                else
                    image.GetPixel()[position_subtract+1] = 0;
                if(image1->GetPixel()[position_input] > image2->GetPixel()[position_input])
                    image.GetPixel()[position_subtract] = image1->GetPixel()[position_input] - image2->GetPixel()[position_input];
                else
                    image.GetPixel()[position_subtract] = 0;
            }
        }
    
}

void Mirror::Execute()
{
    if (image1 == NULL) {
        char msg[128];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = 0;
    int out_height = 0;
    out_width = image1->GetWidth();
    out_height = image1->GetHeight();
    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    for(int i=0; i< image.GetHeight(); i++)
    {
        for(int j=0; j< image.GetWidth(); j++)
        {
            int position_mirror = 3*(i*image.GetWidth()+j);
            int position_input = 3*(i*image.GetWidth() + (image.GetWidth()-(j+1)));
            image.GetPixel()[position_mirror+2] = image1->GetPixel()[position_input+2];
            image.GetPixel()[position_mirror+1] = image1->GetPixel()[position_input+1];
            image.GetPixel()[position_mirror] = image1->GetPixel()[position_input];
        }
    }
}

void Rotate::Execute()
{

    if (image1 == NULL) 
    {
        char msg[128];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = 0;
    int out_height = 0;
    out_width = image1->GetHeight();
    out_height = image1->GetWidth();
    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    for(int i=0; i< image.GetHeight(); i++)
    {
        for(int j=0; j< image.GetWidth(); j++)
        {
            int position_rotate = 3*(i*image.GetWidth()+j);
            int position_input = 3*((image.GetWidth()-j)*image.GetHeight() - (i+1));
            image.GetPixel()[position_rotate] = image1->GetPixel()[position_input];
            image.GetPixel()[position_rotate+1] = image1->GetPixel()[position_input+1];
            image.GetPixel()[position_rotate+2] = image1->GetPixel()[position_input+2];

            if(image.GetWidth()-1 == j)
            {

            }
        }
    }
}

void Grayscale::Execute()
{

    if (image1 == NULL) 
    {
        char msg[128];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = 0;
    int out_height = 0;
    out_width = image1->GetWidth();
    out_height = image1->GetHeight();
    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    for(int i=0; i< image.GetHeight(); i++)
    {
        for(int j=0; j< image.GetWidth(); j++)
        {
            int position_grayscale = 3*(i*image.GetWidth()+j);
            int position_input = 3*(i*image.GetWidth() + j);
            image.GetPixel()[position_grayscale] = image1->GetPixel()[position_input]/5 + image1->GetPixel()[position_input+1]/2 + image1->GetPixel()[position_input+2]/4;
            image.GetPixel()[position_grayscale+1] = image1->GetPixel()[position_input]/5 + image1->GetPixel()[position_input+1]/2 + image1->GetPixel()[position_input+2]/4;
            image.GetPixel()[position_grayscale+2] = image1->GetPixel()[position_input]/5 + image1->GetPixel()[position_input+1]/2 + image1->GetPixel()[position_input+2]/4;
        }
    }
}

void Blur::Execute()
{

     if (image1 == NULL) 
     {
        char msg[128];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int out_width = 0;
    int out_height = 0;
    out_width = image1->GetWidth();
    out_height = image1->GetHeight();
    image.ResetSize(out_width, out_height);
    image.SetPixel();
    image.SetMaxval(255);
    for(int i=0; i< image.GetHeight(); i++)
    {
        for(int j=0; j< image.GetWidth(); j++)
        {   
            
            int position_blur = 3*(i*image.GetWidth()+j);
            int position_input = 3*(i*image.GetWidth()+j);
            int eq1 = image1->GetPixel()[position_input+3]/8 + image1->GetPixel()[position_input-3]/8 + image1->GetPixel()[position_input+ 3*image.GetWidth()]/8 +image1->GetPixel()[position_input - 3*image.GetWidth()]/8;
            
            int eq3 = image1->GetPixel()[position_input+3+1]/8 + image1->GetPixel()[position_input-3+1]/8 + image1->GetPixel()[position_input+ 3*image.GetWidth()+1]/8 +image1->GetPixel()[position_input - 3*image.GetWidth()+1]/8;
            
            int eq5 = image1->GetPixel()[position_input+3+2]/8 + image1->GetPixel()[position_input-3+2]/8 + image1->GetPixel()[position_input + 3*image.GetWidth()+2]/8 +image1->GetPixel()[position_input - 3*image.GetWidth() +2]/8;
            
            
            int eq2 = image1->GetPixel()[position_input+3+3*image.GetWidth()]/8 + image1->GetPixel()[position_input-3-3*image.GetWidth()]/8 + image1->GetPixel()[position_input-3+3*image.GetWidth()]/8 + image1->GetPixel()[position_input+3-3*image.GetWidth()]/8;
            int eq4 = image1->GetPixel()[position_input+3+3*image.GetWidth()+1]/8 + image1->GetPixel()[position_input-3-3*image.GetWidth()+1]/8 + image1->GetPixel()[position_input-3+3*image.GetWidth()+1]/8 + image1->GetPixel()[position_input+3-3*image.GetWidth()+1]/8;
            int eq6 = image1->GetPixel()[position_input+3+3*image.GetWidth()+2]/8 + image1->GetPixel()[position_input-3-3*image.GetWidth()+2]/8 + image1->GetPixel()[position_input-3+3*image.GetWidth()+2]/8 + image1->GetPixel()[position_input+3-3*image.GetWidth()+2]/8;

            
            
            if((i==0 || j==0) || (i==image1-> GetHeight()-1 || j==image1->GetWidth()-1))
            {
            image.GetPixel()[position_blur] = image1->GetPixel()[position_input];;
            image.GetPixel()[position_blur+1] = image1->GetPixel()[position_input+1];;
            image.GetPixel()[position_blur+2] = image1->GetPixel()[position_input+2];;
            }
            else
            {
            image.GetPixel()[position_blur] =eq1 +eq2 ;
            image.GetPixel()[position_blur+1] =eq3 +eq4;
            image.GetPixel()[position_blur+2] =  eq5 +eq6;
            }
        }
    }
}