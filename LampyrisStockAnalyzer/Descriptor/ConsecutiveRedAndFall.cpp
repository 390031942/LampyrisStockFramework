/*
 * File:  ConsecutiveRedAndFall.h
 * Brief: 温和放量(三)连阳形态然后缩量回落两天
 * Author:wushuhong
 * Date： 20223/12/7
*/
#include "ConsecutiveRedAndFall.h"

bool ConsecutiveRedAndFall::satisfied(const StockData& data) const {
    StockPerDayDataPtr pDayData = data.getCurrentDateData();
    if (pDayData != nullptr && pDayData->getPreviousDateData()) {
        StockPerDayDataPtr pFiveDay = pDayData;
        StockPerDayDataPtr pFourDay = pFiveDay->getPreviousDateData();
        StockPerDayDataPtr pThreeDay = pFourDay->getPreviousDateData();
        StockPerDayDataPtr pTwoDay = pThreeDay->getPreviousDateData();
        StockPerDayDataPtr pOneDay = pTwoDay->getPreviousDateData();

        bool condition1 = pOneDay->getVolume() < pTwoDay->getVolume() &&
            pTwoDay->getVolume() < pThreeDay->getVolume();

        bool condition2 = pOneDay->isRise() && pOneDay->isRed() &&
            pTwoDay->isRise() && pTwoDay->isRed() &&
            pThreeDay->isRise() && pThreeDay->isRed();

        bool condition3 = pThreeDay->getTurnOverRate() > 5.00f;

        bool condition4 = (pOneDay->getTurnOverRate() + pTwoDay->getTurnOverRate() + pThreeDay->getTurnOverRate()) > 8.0f;

        // float percentage = pOneDay->getPercentage() + pTwoDay->getPercentage() + pThreeDay->getPercentage();
        bool condition5 = true;//  percentage > 3.0f && percentage < 15.0f;

        bool condition6 = pFourDay->isFall() && pFourDay->isGreen() &&
            pFiveDay->isFall() && pFiveDay->isGreen();

        bool condition7 = pThreeDay->getVolume() > pFourDay->getVolume() &&
            pFourDay->getVolume() > pFiveDay->getVolume();

        return condition1 && condition2 && condition3 && condition4 && condition5 && condition6 && condition7;
    }

    return false;
}
