#include <iostream>
#include<source.h>
#include<sink.h>

#ifndef FILTER_H
#define FILTER_H
class filter : public source , public sink
{
  void Update();
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
protected:
float factor;
public:
void SetFactor(float fact);
void Execute();
};


#endif