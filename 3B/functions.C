#include<image.h>
#include<functions.h>

void ReadImage(char *filename, Image &output)
{
    FILE *fptr = fopen(filename, "rb");
    int height = 0; int width = 0; int maxval = 0; char magic_num[128];

    fscanf(fptr, "%s\n%d  %d \n %d\n ", magic_num, &width, &height, &maxval);
    
  //  unsigned char *pixel = new unsigned char(3*width*height);
    //cout<<"\n pixel memory allocated\n";
    

    output.ResetSize(width, height);
    output.SetPixel();
    fread(output.GetPixel(), sizeof(unsigned char), 3*output.GetWidth()*output.GetHeight(), fptr);
    cout<<"file read to pixel pointer \n";
    output.SetMaxval(maxval);
    cout<<"Image Read \n";
    fclose(fptr);
    

}

void HalfSize(Image &input, Image &output)
{
    int out_width = input.GetWidth()/2;
    int out_height = input.GetHeight()/2;

    output.ResetSize(out_width, out_height);
    output.SetPixel();
    output.SetMaxval(255);

    for (int i = 0; i< output.GetHeight(); i++)
    {
        for (int j = 0; j< output.GetWidth(); j++)
        {
            output.GetPixel()[3*(i*output.GetWidth() + j)] =input.GetPixel()[3* (i*input.GetWidth()*2 + 2*j )];
            output.GetPixel()[3*(i*output.GetWidth() + j) + 1] =input.GetPixel()[3* (i*input.GetWidth()*2 + 2*j ) + 1];
            output.GetPixel()[3*(i*output.GetWidth() + j) + 2] =input.GetPixel()[3* (i*input.GetWidth()*2 + 2*j ) + 2];
        }
    }


}

void LeftRightCombine(Image &left, Image &right, Image &output)
{
    int out_height = 0;
    if(left.GetHeight() > right.GetHeight())
    {
        out_height = left.GetHeight();
    }
    else
    {
        out_height = right.GetHeight();
    }
    int out_width = left.GetWidth() + right.GetWidth();
    

    output.ResetSize(out_width, out_height);
    output.SetPixel();
    output.SetMaxval(255);
    for (int i =0; i< output.GetHeight(); i++)
    {
        for(int j=0; j< output.GetWidth(); j++)
        {
            int position = 3*(i*output.GetWidth()+j);
            if(j<left.GetWidth())
            {   
                int position_left = 3*(i*left.GetWidth()+j);
                output.GetPixel()[position] = left.GetPixel()[position_left];
                output.GetPixel()[position+1] = left.GetPixel()[position_left+1];
                output.GetPixel()[position+2] = left.GetPixel()[position_left+2];
            }
            else
            {   int position_right = 3*(i*right.GetWidth()+j);
                output.GetPixel()[position] = right.GetPixel()[position_right];
                output.GetPixel()[position+1] = right.GetPixel()[position_right+1];
                output.GetPixel()[position+2] = right.GetPixel()[position_right+2];
            }

        }
    }
}

void TopBottomCombine(Image &upper, Image &lower, Image &output)
{
    int out_width = 0;
    if(upper.GetWidth() > lower.GetWidth())
    {
        out_width = upper.GetWidth();
    }
    else
    {
        out_width = lower.GetWidth();
    }
    int out_height = lower.GetHeight() + upper.GetHeight();
    

    output.ResetSize(out_width, out_height);
    output.SetPixel();
    output.SetMaxval(255);
    for (int i =0; i< upper.GetHeight(); i++)
    {
        for(int j=0; j< output.GetWidth(); j++)
        {
            int position = 3*(i*output.GetWidth()+j);
            
               
            int position_upper = 3*(i*upper.GetWidth()+j);
            output.GetPixel()[position] = upper.GetPixel()[position_upper];
            output.GetPixel()[position+1] = upper.GetPixel()[position_upper+1];
            output.GetPixel()[position+2] = upper.GetPixel()[position_upper+2];
        }
    }
    for (int i =0; i< lower.GetHeight(); i++)
    {
        for(int j=0; j< output.GetWidth(); j++)
        {
                int position = 3*upper.GetHeight()*upper.GetWidth() + 3*(i*output.GetWidth()+j);
                int position_lower = 3*(i*lower.GetWidth()+j);
                output.GetPixel()[position] = lower.GetPixel()[position_lower];
                output.GetPixel()[position+1] = lower.GetPixel()[position_lower+1];
                output.GetPixel()[position+2] = lower.GetPixel()[position_lower+2];
        }
    }
}

void Blend(Image &input1, Image &input2, double factor, Image &output)
{
    int out_width = 0;
    int out_height = 0;

    if(input1.GetWidth()>input2.GetWidth())
        out_width = input1.GetWidth();
    else
        out_width = input2.GetWidth();

    if(input1.GetHeight()>input2.GetHeight())
        out_height = input1.GetHeight();
    else
        out_height = input2.GetHeight();
    
    output.ResetSize(out_width, out_height);
    output.SetPixel();
    output.SetMaxval(255);

    for (int i = 0; i< output.GetHeight(); i++)
    {
        for (int j = 0; j< output.GetWidth(); j++)
        {      int position = 3* (i*output.GetWidth()+j);
                int i1_position = 3*(i*input1.GetWidth()+j);
                int i2_position = 3*(i*input2.GetWidth()+j);
            output.GetPixel()[position] =factor*input1.GetPixel()[i1_position] + (1-factor)*input2.GetPixel()[i2_position];
            output.GetPixel()[position+1] =factor*input1.GetPixel()[i1_position+1] + (1-factor)*input2.GetPixel()[i2_position+1];
            output.GetPixel()[position+2] =factor*input1.GetPixel()[i1_position+2] + (1-factor)*input2.GetPixel()[i2_position+2];
        }
    }
}

void WriteImage(char *filename, Image &img)
{
    FILE *fptr = fopen(filename, "wb");
    cout<<"new file opened \n";
    fprintf(fptr, "P6\n %d  %d\n %d\n", img.GetWidth(), img.GetHeight(), img.GetMaxval());
    cout<<"written image values to output \n";
    cout<<"\n"<<img.GetWidth()<< "  "<<img.GetHeight()<<"\n";
    fwrite(img.GetPixel(), sizeof(unsigned char), 3*img.GetHeight()*img.GetWidth(), fptr);
    cout<<"Image Written to output\n";
    fclose(fptr);
}

