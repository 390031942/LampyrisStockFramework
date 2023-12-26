/*
 * File:  StockData.cpp
 * Brief: �����˹�Ʊÿ������(k������)�����Ʊ��������(ÿ������)�����ݽṹ
 * Author:wushuhong
 * Date�� 20223/12/5
*/

// Project Include(s)
#include "StockData.h"

StockPerDayData::StockPerDayData(StockPerDayDataPtr prev, StockPerDayDataPtr next) {
    this->m_pPrevious = prev;
    this->m_pNext = next;
}

StockPerDayData::~StockPerDayData() {}

bool StockPerDayData::isGapUpOpen() const {
    if (this->m_pPrevious != nullptr) {
        return this->m_pPrevious->m_highestPrice < this->m_openPrice;
    }
    return false;
}

bool StockPerDayData::isGapDownOpen() const {
    if (this->m_pPrevious != nullptr) {
        return this->m_pPrevious->m_lowestPrice > this->m_openPrice;
    }
    return false;
}

bool StockPerDayData::isGreen() const {
    return this->m_openPrice > this->m_closePrice;
}

bool StockPerDayData::isRed() const {
    return this->m_openPrice <= this->m_closePrice;
}

bool StockPerDayData::isRise() const {
    return this->m_closePrice > this->getLastClosePrice();
}

bool StockPerDayData::isFall() const {
    return this->m_closePrice < this->getLastClosePrice();
}
