#include<source.h>

#ifndef PNMREADER_H
#define PNMREADER_H


class PNMreader: public source
{
    private:
    char *filename;

    public:
    void Execute();
    PNMreader();
    PNMreader(char *fname);
    ~PNMreader();
};
#endif

