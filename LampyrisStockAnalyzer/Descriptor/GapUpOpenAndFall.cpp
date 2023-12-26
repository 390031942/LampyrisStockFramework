/*
 * File:  GapUpOpenAndFall.cpp
 * Brief: 跳空高开回落收绿K + 第二天低开高走收红线
 * Author:wushuhong
 * Date： 2023/12/11
*/
#include "GapUpOpenAndFall.h"

bool GapUpOpenAndFall::satisfied(const StockData& data) const {
    StockPerDayDataPtr pDayData = data.getCurrentDateData();
    if (pDayData != nullptr && pDayData->getPreviousDateData()) {
        StockPerDayDataPtr pTwoDay = pDayData;
        StockPerDayDataPtr pOneDay = pTwoDay->getPreviousDateData();

        bool condition1 = pOneDay->isGapUpOpen() && pOneDay->isGreen() && pOneDay->isRise();
        bool condition2 = pTwoDay->getOpenPrice() < pOneDay->getClosePrice() &&
            pTwoDay->getClosePrice() < pOneDay->getClosePrice() &&
            (pTwoDay->isRed());
        bool condition3 = std::max(pOneDay->getTurnOverRate(), pTwoDay->getTurnOverRate()) > 5.0f;
        bool condition4 = true; pOneDay->getVolume() > pTwoDay->getVolume();

        return condition1 && condition2 && condition3 && condition4;
    }

    return false;
}
