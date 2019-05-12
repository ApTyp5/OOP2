#pragma once

#include <time.h>
#include "miterator.h"
#include "matrix.h"

template<typename T>
size_t Matrix<T>::init_list_matrix_rate(std::initializer_list<std::initializer_list<T> > &list)
{
    size_t rate = list.size();

    for (auto &el: list)
    {
        rate = (el.size() > rate) ? el.size() : rate;
    }

    return rate;
}

template<typename T>
Matrix<T>::~Matrix()
{}

template<typename T>
Matrix<T>::Matrix(size_t len, size_t wid, T **mat):
    //BaseMatrix (len, wid), data(new Raw[len], [](T *p){delete [] p;})
    BaseMatrix (len, wid), data(new T[len * wid])
{
    if (data.get() == nullptr)
    {
        throw alloc_err(time(nullptr), typeid(*this).name(), __FUNCTION__);
    }

    if (mat)
    {
        for (size_t i = 0; i < len; i++)
        {
            for (size_t j = 0; j < wid; j++)
            {
                (*this)[i][j] = (*mat)[i * wid + j];
            }
        }
    }
}

template<typename T>
Matrix<T>::Matrix(size_t len, size_t wid, const T &init):
    Matrix(len, wid)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < wid; j++)
        {
            (*this)[i][j] = init;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
{
    size_t rate = init_list_matrix_rate(list);
    len = rate;
    wid = rate;
    data.reset(new T[len * wid]);

    if (data.get() == nullptr)
    {
        throw alloc_err(time(nullptr), typeid (*this).name(), __FUNCTION__);
    }


    size_t i = 0;
    size_t j = 0;
    for (auto &raw : list)
    {
        j = 0;
        for (auto &el : raw)
        {
            (*this)[i][j] = el;
            j++;
        }
        i++;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &mtr):
    Matrix(mtr.getLen(), mtr.getWid())
{
    for (size_t i = 0; i < mtr.getLen(); i++)
    {
        for (size_t j = 0; j < mtr.getWid(); j++)
        {
            (*this)[i][j] = mtr[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &&mtr):
    BaseMatrix (len, wid)
{
    data.reset(mtr.data.get());
    mtr.data.reset();
}

template<typename T>
void Matrix<T>::fill(const T &init) noexcept
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < wid; j++)
        {
            (*this)[i][j] = init;
        }
    }
}

template<typename T>
void Matrix<T>::swap(size_t raw1, size_t col1, size_t raw2, size_t col2)
{
    if (raw1 < len || raw2 < len ||
        col1 < wid || col2 < wid)
    {
        throw out_of_range(__func__,__FILE__,__LINE__);
    }
    T tmp = (*this)[raw1][col1];
    (*this)[raw1][col1] = (*this)[raw2][col2];
    (*this)[raw2][col2] = tmp;
}


template<typename T>
const T &Matrix<T>::operator()(size_t i, size_t j) const
{
    return (data.get() + i)[j];
}

template<typename T>
T &Matrix<T>::operator()(size_t i, size_t j)
{
    return (data.get() + i)[j];
}

template<typename T>
typename Matrix<T>::Raw Matrix<T>::operator[](size_t raw)
{
    return Raw(data.get(), raw, len, wid);
}

template<typename T>
const typename Matrix<T>::Raw Matrix<T>::operator[](size_t raw) const
{
    return Raw(data.get(), raw, len, wid);
}


template<typename T>
Matrix<T> Matrix<T>::operator +(const Matrix<T> &mtr) const
{
    if (this->getLen() != mtr.getLen() ||
        this->getWid() != mtr.getWid())
    {
        throw wrong_sizes(__func__,__FILE__,__LINE__);
    }

    Matrix<T> result(len, wid);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < wid; j++)
        {
            result[i][j] = (*this)[i][j] + mtr[i][j];
        }
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator -(const Matrix<T> &mtr) const
{
    if (this->getLen() != mtr.getLen() ||
        this->getWid() != mtr.getWid())
    {
        throw wrong_sizes(__func__,__FILE__,__LINE__);
    }

    Matrix<T> result(len, wid);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < wid; j++)
        {
            result[i][j] = (*this)[i][j] - mtr[i][j];
        }
    }

    return result;
}

template<typename T>
const Matrix<T> & Matrix<T>::operator +=(const Matrix<T> &mtr)
{
    if (this->getLen() != mtr.getLen() ||
        this->getWid() != mtr.getWid())
    {
        throw wrong_sizes(__func__,__FILE__,__LINE__);
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < wid; j++)
        {
            (*this)[i][j] += mtr[i][j];
        }
    }

    return *this;
}

template<typename T>
const Matrix<T> & Matrix<T>::operator -=(const Matrix<T> &mtr)
{
    if (this->getLen() != mtr.getLen() ||
        this->getWid() != mtr.getWid())
    {
        throw wrong_sizes(__func__,__FILE__,__LINE__);
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < wid; j++)
        {
            (*this)[i][j] -= mtr[i][j];
        }
    }
}



template<typename T>
Matrix<T> Matrix<T>::operator =(const Matrix<T> &mtr)
{
    Matrix<T> result(mtr);
    return result;
}

template<typename T>
Matrix<T> operator *(const T &el, const Matrix<T> &mtr)
{
    Matrix<T> answer(mtr);
    for (int i = 0; i < mtr.getLen(); i++)
    {
        for (int j = 0; j < mtr.getWid(); j++)
        {
            answer[i][j] *= el;
        }
    }
    return answer;
}

template<typename T>
Matrix<T> Matrix<T>::operator =(Matrix<T> &&mtr) noexcept
{
    Matrix<T> result(mtr);
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator *(const T &el) const
{
    Matrix<T> result(*this);
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < wid; j++)
        {
            result[i][j] *= el;
        }
    }

    return result;
}


template<typename T>
const Matrix<T> &Matrix<T>::operator *=(const T &el) noexcept
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < wid; j++)
        {
            (*this)[i][j] *= el;
        }
    }

    return (*this);
}

template<typename T>
Matrix<T> Matrix<T>::operator *(const Matrix<T> &mtr)
{
    if (wid != mtr.getLen())
    {
        throw wrong_sizes(__func__,__FILE__,__LINE__);
    }

    Matrix<double> result(len, mtr.getWid(), 0);

    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < mtr.getWid(); j++)
        {
            for (size_t k = 0; k < wid; k++)
            {
                result[i][j] += (*this)[i][j] * mtr[i][j];
            }
        }
    }

    return result;
}

template<typename T>
const Matrix<T> &Matrix<T>::operator *=(const Matrix<T> &mtr)
{
    if (wid != mtr.getLen() ||
        wid != mtr.getWid())
    {
        throw wrong_sizes(__func__,__FILE__,__LINE__);
    }

    (*this) = (*this) * mtr;
    return *this;
}



template<typename T>
Matrix<T> Matrix<T>::addMinor(size_t raw, size_t col) const
{
    if (len != wid || len == 1 || wid == 1)
    {
        throw  wrong_sizes(__func__,__FILE__,__LINE__);
    }

    Matrix<double> result(len - 1, wid - 1);
    for (size_t i = 0; i < raw - 1; i++)
    {
        for (size_t j = 0; j < col - 1; j++)
        {
            result[i][j] = (*this)[i][j];
        }
    }

    for (size_t i = raw + 1; i < len; i++)
    {
        for (size_t j = col + 1; j < wid; j++)
        {
            result[i - 1][j - 1] = (*this)[i][j];
        }
    }

    return result;
}


template<typename T>
double Matrix<T>::det() const
{
    if (len != wid)
    {
        throw wrong_sizes(__func__,__FILE__,__LINE__);
    }

    if (len == 1)
    {
        return (*this)[0][0];
    }

    int sig = 1;
    double result = 0;

    for (size_t j = 0; j < wid; j++)
    {
        Matrix<double> M = addMinor(0, j);
        result += sig * (*this)[0][j] * M.det();
        sig *= -1;
    }

    return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator ~()
{
    Matrix<double> result = this->transpose();
    double reverse_det = 1.0 / this->det();

    result *= reverse_det;
    return result;
}



template<typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> result(wid, len);

    for (size_t i = 0; i < wid; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            result[i][j] = (*this)[j][i];
        }
    }

    return result;
}

template<typename T>
const Matrix<T> & Matrix<T>::self_transpese()
{
    Matrix<T> result(*this);
    delete this;
    this = result.transpose();

    return *this;
}


template<typename T>
MIterator<T> Matrix<T>::begin()
{
    MIterator<T> iter(data, 0, len * wid);
    return iter;
}

template<typename T>
MIterator<T> Matrix<T>::end()
{
    size_t size = len * wid;

    MIterator<T> iter(data, size, size);
    return iter;
}

template<typename T>
cMIterator<T> Matrix<T>::cbegin() const
{
    cMIterator<T> iter((std::shared_ptr<double> &)data, 0, len * wid);
    return iter;
}

template<typename T>
cMIterator<T> Matrix<T>::cend() const
{
    size_t size = len * wid;

    cMIterator<T> iter((std::shared_ptr<double> &)data, size, size);
    return iter;
}



template<typename T>
T &Matrix<T>::Raw::operator[](size_t index)
{
    if ( !(0 <= index && index < colNum) )
    {
        throw out_of_range(time(nullptr), typeid (*this).name(),
                           __FUNCTION__,
                           "bad index");
    }
    if (curRaw >= rawNum)
    {
        throw out_of_range(time(nullptr), typeid (*this).name(),
                           __FUNCTION__,
                           "bad raw");
    }
    return *(data + curRaw * colNum + index);
}

template<typename T>
Matrix<T>::Raw::Raw(Raw &&tmp): data(tmp.data), curRaw(tmp.curRaw),
    rawNum(tmp.rawNum), colNum(tmp.colNum)
{
    tmp.data = nullptr;
    tmp.rawNum = -1;
    tmp.colNum = -1;
    tmp.curRaw = -1;
}


template<typename T>
Matrix<T>::Raw::Raw(T *data, size_t curRaw, size_t rawNum, size_t colNum):
    data(data), curRaw(curRaw), rawNum(rawNum), colNum(colNum)
{
    if (data == nullptr)
    {
        throw bad_ptr(time(nullptr), typeid (*this).name(), __FUNCTION__);
    }
}


template<typename T>
bool Matrix<T>::operator ==(Matrix<T> &mtr)
{
    if (len != mtr.getLen() || wid != mtr.getWid())
    {
        return false;
    }

    for (auto i = cbegin(), j = mtr.cbegin(); i != cend(); i++, j++)
    {
        if (*i != *j)
        {
            return false;
        }
    }

    return true;
}

template <typename T>
bool Matrix<T>::operator !=(Matrix<T> &mtr)
{
    return ! (this->operator==(mtr));
}


template<typename T>
const T &Matrix<T>::at(size_t i, size_t j) const
{
    return (*this)[i][j];
}



template<typename T>
Matrix<T> Matrix<T>::add(const Matrix<T> &mtr) const
{
    return (*this) + mtr;
}

template<typename T>
Matrix<T> Matrix<T>::sub(const Matrix<T> &mtr) const
{
    return (*this) - mtr;
}

template<typename T>
const Matrix<T> & Matrix<T>::selfAdd(const Matrix<T> &mtr)
{
    return (*this) += mtr;
}

template<typename T>
const Matrix<T> & Matrix<T>::selfSub(const Matrix<T> &mtr)
{
    return (*this) -= mtr;
}

template<typename T>
Matrix<T> Matrix<T>::mult(const T &el)
{
    return (*this) * el;
}

template<typename T>
const Matrix<T> &Matrix<T>::selfMult(const T &el) noexcept
{
    return (*this) *= el;
}


template <typename T>
Matrix<T> Matrix<T>::mult(const Matrix<T> &mtr)
{
    return (*this) * mtr;
}

template <typename T>
const Matrix<T> Matrix<T>::selfMult(const Matrix<T> &mtr)
{
    return (*this) *= mtr;
}


template <typename T>
Matrix<T> Matrix<T>::revert()
{
    return ~(*this);
}
