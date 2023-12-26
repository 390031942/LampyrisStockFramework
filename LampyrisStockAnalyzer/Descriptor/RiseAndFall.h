/*
 * File:  RiseAndFall.h
 * Brief: ��߻���/�γ�(��)��Ӱ��
 * Author:wushuhong
 * Date�� 20223/12/5
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

class RiseAndFall :public AbstractStockKLineDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;

    virtual bool satisfied(const StockPerDayData& data) const;
};
