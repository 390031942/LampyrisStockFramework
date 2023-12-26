/*
 * File:  StockDescriptor.h
 * Brief: 定义了股票每日数据(k线)形态,与股票k线走势形态的描述基类
 * Author:wushuhong
 * Date： 20223/12/5
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

