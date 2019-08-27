#include <iostream>
#include<source.h>
#include<sink.h>
/*
void ReadImage(char *filename, Image &output);
void WriteImage(char *filename, Image &img);

void HalfSize(Image &input, Image &output);

void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output);

void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output);
void Blend(Image &input1, Image &input2, double factor, Image &output); 
*/
#ifndef FILTER_H
#define FILTER_H
class filter : public source , public sink
{

};

class Shrinker : public filter
{
public:
void Execute();
};

class LRCombine : public filter
{
public:
void Execute();
};

class TBCombine : public filter
{
public:
void Execute();
};

class Blender : public filter
{
public:
float factor;
public:
void SetFactor(float fact);
void Execute();
};


#endif