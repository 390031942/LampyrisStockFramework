/*
 * File:  BigRedAndTwoGreen.h
 * Brief: =һ�������ߺ�����������
 * Author:wushuhong
 * Date�� 2023/12/11
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"
#include "Descriptor/RiseAndFall.h"

class BigRedAndTwoGreen :public AbstractStockTrendDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;
};