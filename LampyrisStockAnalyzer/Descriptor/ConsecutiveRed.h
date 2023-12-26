/*
 * File:  ConsecutiveRed.h
 * Brief: 温和放量(三)连阳形态
 * Author:wushuhong
 * Date： 20223/12/5
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

class ConsecutiveRed :public AbstractStockTrendDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;
};