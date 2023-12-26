/*
 * File:  ConsecutiveRedAndFall.h
 * Brief: 温和放量(三)连阳形态然后缩量回落两天
 * Author:wushuhong
 * Date： 20223/12/7
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

class ConsecutiveRedAndFall :public AbstractStockTrendDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;
};