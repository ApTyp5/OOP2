#ifndef BASEMATRIX_H
#define BASEMATRIX_H

#include <stdlib.h>

class BaseMatrix
{
public:
    BaseMatrix(){}
    BaseMatrix(size_t len, size_t wid): len(len), wid(wid) {}
    size_t getLen() const { return len; }
    size_t getWid() const { return wid; }
    size_t Size()   const { return len * wid; }



protected:
    size_t len, wid;

};

#endif // BASEMATRIX_H
