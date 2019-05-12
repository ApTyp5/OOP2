#pragma once
#include "iterators.hpp"



template<typename T>
class MIterator: public Iterator<T>
{
public:
    ~MIterator(){}
    MIterator(std::shared_ptr<T> &el_ptr, size_t cur_num, size_t wid):
        Iterator<T>(el_ptr, cur_num, wid){}

    MIterator(const MIterator &iter):
        Iterator<T>(iter){}

    MIterator(MIterator &&iter):
        Iterator<T>(iter){}

    T &operator *();
    const T& operator *() const;
    T *operator ->();
    const T *operator ->() const;
};



template<typename T>
class cMIterator: public Iterator<T>
{
public:
    ~cMIterator(){}
    cMIterator(std::shared_ptr<T> &el_ptr, size_t cur_num, size_t wid):
        Iterator<T>(el_ptr, cur_num, wid){}

    cMIterator(const cMIterator &iter):
        Iterator<T>(iter){}

    cMIterator(cMIterator &&iter):
        Iterator<T>(iter){}

    const T &operator *();
    const T *operator ->();
};


