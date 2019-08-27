#include<source.h>
#include<image.h>

Image* source::GetOutput()
{
    return &image;
}

source::source()
{
    image.setsource(this);
}

void source::Update()
{
Execute();
}

