/*
 * File:  ConsecutiveRedAndFall.h
 * Brief: �ºͷ���(��)������̬Ȼ��������������
 * Author:wushuhong
 * Date�� 20223/12/7
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

class ConsecutiveRedAndFall :public AbstractStockTrendDescriptor {
public:
    virtual bool satisfied(const StockData& data) const;
};