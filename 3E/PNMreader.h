#include<source.h>
#include<string.h>

#ifndef PNMREADER_H
#define PNMREADER_H


class PNMreader: public source
{
    protected:
    char *filename;

    public:
    virtual void Execute();
    PNMreader();
    PNMreader(char *fname);
    ~PNMreader();
};
#endif

