/*
 * File:  RiseAndFall.h
 * Brief: 冲高回落/形成(长)上影线
 * Author:wushuhong
 * Date： 20223/12/5
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

class RiseAndFall :public AbstractStockKLineDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;

    virtual bool satisfied(const StockPerDayData& data) const;
};
