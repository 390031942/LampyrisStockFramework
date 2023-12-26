/*
 * File:  GapUpOpenAndFall.h
 * Brief: 跳空高开回落收绿K + 第二天低开高走收红线
 * Author:wushuhong
 * Date： 2023/12/11
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

class GapUpOpenAndFall :public AbstractStockTrendDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;
};