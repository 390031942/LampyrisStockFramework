/*
 * File:  GapUpOpenAndFall.h
 * Brief: ���ո߿���������K + �ڶ���Ϳ������պ���
 * Author:wushuhong
 * Date�� 2023/12/11
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

class GapUpOpenAndFall :public AbstractStockTrendDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;
};