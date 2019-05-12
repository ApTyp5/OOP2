#pragma once
#include "iterators.h"
#include "exception.h"




template<typename T>
Iterator<T>::~Iterator()
{}

template<typename T>
Iterator<T>::Iterator(std::shared_ptr<T> &sh_ptr, size_t cur_num, size_t max_num):
    data(sh_ptr), cur_num(cur_num), max_num(max_num)
{
    if (data.expired() == true)
    {
        throw damaged_iter(time(nullptr), typeid(*this).name(), __FUNCTION__);
    }
}


template<typename T>
Iterator<T>::operator bool() const
{
    return !data.expired();
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T> &iter):
    data(iter.data), cur_num(iter.cur_num), max_num(iter.max_num)
{}

template<typename T>
Iterator<T>::Iterator(Iterator &&iter):
    data(std::move(iter.data)),
    cur_num(iter.cur_num), max_num(iter.max_num)
{
    iter.data.reset();
    iter.cur_num = 0;
    iter.max_num = 0;
}


template<typename T>
bool Iterator<T>::operator ==(const Iterator<T> &iter) const
{
    return cur_num == iter.cur_num;
}

template<typename T>
bool Iterator<T>::operator !=(const Iterator<T> &iter) const
{
    return cur_num != iter.cur_num;
}


template<typename T>
Iterator<T> Iterator<T>::operator +(int step)
{
    int delta = cur_num + step;

    if ( !(0 <= delta && delta < max_num) )
    {
        throw out_of_range(time(nullptr), typeid (*this).name(), __FUNCTION__);
    }

    std::shared_ptr<T> ptr = data.lock();
    Iterator<T> result(ptr.get(), size_t(delta), max_num);

    return result;
}

template<typename T>
const Iterator<T> &Iterator<T>::operator +=(int step)
{
    int delta = cur_num + step;

    if ( !(0 <= delta && size_t(delta) <= max_num) )
    {
        throw out_of_range(time(nullptr), typeid (*this).name(), __FUNCTION__);
    }

    cur_num = size_t(delta);

    return (*this);
}

template<typename T>
const Iterator<T> &Iterator<T>::operator ++()
{
    return ( (*this) += 1 );
}

template<typename T>
Iterator<T> Iterator<T>::operator ++(int)
{
    Iterator<T> result(*this);
    ++(*this);

    return result;
}

template<typename T>
Iterator<T> Iterator<T>::operator -(int step)
{
    step = -step;
    return (*this) + step;
}

template<typename T>
const Iterator<T> &Iterator<T>::operator -=(int step)
{
    step = -step;
    return (*this) += step;
}

template<typename T>
Iterator<T> Iterator<T>::operator --()
{
    return  ( (*this) -= 1);
}

template<typename T>
Iterator<T> Iterator<T>::operator --(int)
{
    Iterator<T> result(*this);
    --(*this);

    return result;
}








/*
template<typename T>
T &Iterator<T>::operator *()
{
    if (bool(data.lock()) == false)
    {
        throw damaged_iter(time(nullptr), typeid(*this).name(), __FUNCTION__);
    }

    std::shared_ptr<T> ptr = data.lock();
    return *(ptr.get() + cur_num);
}
*/
/*
template<typename T>
T * Iterator<T>::operator ->()
{
    if (data.get() == nullptr)
    {
        throw bad_ptr(time(nullptr), typeid(*this).name(), __FUNCTION__);
    }
    return data.get();
}
*/
/*
template<typename T>
const T * Iterator<T>::operator ->() const
{
    if (data.get() == nullptr)
    {
        throw bad_ptr(time(nullptr), typeid(*this).name(), __FUNCTION__);
    }
    return data.get();
}
*/
/*
template<typename T>
const T &Iterator<T>::operator *() const
{
    if (bool(data.lock()) == false)
    {
        throw damaged_iter(time(nullptr), typeid(*this).name(), __FUNCTION__);
    }

    std::shared_ptr<T> ptr = data.lock();
    return *(ptr.get() + cur_num);
}
*/
