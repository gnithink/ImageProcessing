#include <iostream>
#include<source.h>
#include<sink.h>

#ifndef FILTER_H
#define FILTER_H
class filter : public source , public sink
{
  public:
  virtual void Update();
  virtual const char *FilterName() = 0;
  virtual const char *SourceName();
  virtual const char *SinkName();
};

class Shrinker : public filter
{
public:
virtual void Execute();
virtual const char *FilterName();
};

class LRCombine : public filter
{
public:
virtual void Execute();
virtual const char *FilterName();
};

class TBCombine : public filter
{
public:
virtual void Execute();
virtual const char *FilterName();
};

class Blender : public filter
{
protected:
float factor;
public:
void SetFactor(float fact);
virtual void Execute();
virtual const char *FilterName();

};

class Subtract: public filter
{
public:
virtual void Execute();
virtual const char *FilterName();
};

class Mirror: public filter
{
public:
void Execute();
virtual const char *FilterName();
};

class Rotate:public filter
{
public:
void Execute();
virtual const char *FilterName();
};
class Grayscale: public filter
{
public:
void Execute();
virtual const char *FilterName();
};
class Blur : public filter
{
public:
void Execute();
virtual const char *FilterName();
};

#endif