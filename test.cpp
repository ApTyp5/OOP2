#include <QtTest/QTest>

#include "matrix.hpp"
#include "miterator.hpp"




class MatrixTest: public QObject
{Q_OBJECT
private slots:
    void createTest();
    void listCreateTest();
    void iterTest();
    void iterTest_02();

};



void MatrixTest::createTest()
{
    size_t len = 3;
    size_t wid = 3;
    double init = 3;

    Matrix<double> mtr(len, wid, init);
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < wid; j++)
        {
            QCOMPARE(mtr[i][j], init);
        }
    }
}

void MatrixTest::listCreateTest()
{
    size_t len = 3;
    size_t wid = 3;

    Matrix<double> mtr {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < wid; j++)
        {
            QCOMPARE(mtr[i][j], double(i * wid + j + 1));
        }
    }

}

void MatrixTest::iterTest()
{
    Matrix<double> mtr {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    size_t j = 1;
    for (auto i = mtr.cbegin(); i != mtr.cend(); i++)
    {
        QCOMPARE(size_t(*i), j);
        j++;
    }
}

void MatrixTest::iterTest_02()
{
    const size_t len = 5, wid = 3;
    Matrix<double> mtr(len, wid);
    auto iter = mtr.begin();
    int j = 1;

    while (iter != mtr.end())
    {
        *iter = j;
        iter++;
        j++;
    }

    Matrix<double> mtr2(len, wid);
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < wid; j++)
        {
            mtr2[i][j] = i * wid + j + 1;
        }
    }

    QVERIFY(mtr == mtr2);
}





QTEST_MAIN(MatrixTest);
#include <test.moc>


