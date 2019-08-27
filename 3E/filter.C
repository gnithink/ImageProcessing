
#include<filter.h>
#include<source.h>
#include<sink.h>


void filter::Update()
{
    if(image1 !=NULL)
    {
        image1->Update();
        Execute();
    }
    if(image2 !=NULL)
    {
        image2->Update();
        Execute();
    }

}

void Shrinker::Execute()
{
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
    int out_width = 0;
    int out_height = 0;

    if(image1->GetWidth()>image2->GetWidth())
        out_width = image1->GetWidth();
    else
        out_width = image2->GetWidth();

    if(image1->GetHeight()>image2->GetHeight())
        out_height = image1->GetHeight();
    else
        out_height = image2->GetHeight();
    
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