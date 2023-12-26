/*
 * File:  ConsecutiveRed.h
 * Brief: 温和放量(三)连阳形态
 * Author:wushuhong
 * Date： 20223/12/5
*/
#include "ConsecutiveRed.h"

bool ConsecutiveRed::satisfied(const StockData& data) const {
    StockPerDayDataPtr pDayData = data.getCurrentDateData();
    if (pDayData != nullptr && pDayData->getPreviousDateData() && pDayData->getPreviousDateData()->getPreviousDateData()) {
        StockPerDayDataPtr pOneDay = pDayData->getPreviousDateData()->getPreviousDateData();
        StockPerDayDataPtr pTwoDay = pDayData->getPreviousDateData();
        StockPerDayDataPtr pThreeDay = pDayData;

        bool condition1 = pOneDay->getVolume() < pTwoDay->getVolume() &&
            pTwoDay->getVolume() < pThreeDay->getVolume();

        bool condition2 = pOneDay->isRise() && pOneDay->isRed() &&
            pTwoDay->isRise() && pTwoDay->isRed() &&
            pThreeDay->isRise() && pThreeDay->isRed();

        bool condition3 = pThreeDay->getTurnOverRate() > 5.00f;

        bool condition4 = (pOneDay->getTurnOverRate() + pTwoDay->getTurnOverRate() + pThreeDay->getTurnOverRate()) > 9.0f;

        float percentage = pOneDay->getPercentage() + pTwoDay->getPercentage() + pThreeDay->getPercentage();
        bool condition5 = percentage > 3.0f && percentage < 10.0f;

        return condition1 && condition2 && condition3 && condition4 && condition5;
    }

    return false;
}
