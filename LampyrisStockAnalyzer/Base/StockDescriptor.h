/*
 * File:  StockDescriptor.h
 * Brief: �����˹�Ʊÿ������(k��)��̬,���Ʊk��������̬����������
 * Author:wushuhong
 * Date�� 20223/12/5
*/
#pragma once

// Project Include(s)
#include "StockData.h"

class AbstractStockTrendDescriptor {
public:
    virtual bool satisfied(const StockData& data) const = 0;
};

class AbstractStockKLineDescriptor {
public:
    virtual bool satisfied(const StockPerDayData& data) const = 0;
};

