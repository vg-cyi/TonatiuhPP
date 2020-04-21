#pragma once

#include <QMutex>
#include <QObject>

#include "RandomDeviate.h"


class ParallelRandomDeviate:  public QObject, public RandomDeviate
{
    Q_OBJECT

public:
    ParallelRandomDeviate(RandomDeviate* rand, QMutex* mutex, unsigned long arraySize = 100000, QObject* parent = 0);
    virtual ~ParallelRandomDeviate();
    void FillArray(double* array, const unsigned long arraySize);

private:
    RandomDeviate* m_pRand;
    QMutex* m_mutex;
};
