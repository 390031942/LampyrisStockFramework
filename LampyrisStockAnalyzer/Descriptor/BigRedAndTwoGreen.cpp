/*
 * File:  BigRedAndTwoGreen.cpp
 * Brief: =一根大阳线后缩量两连阴
 * Author:wushuhong
 * Date： 2023/12/11
*/
#include "BigRedAndTwoGreen.h"

bool BigRedAndTwoGreen::satisfied(const StockData& data) const {
	StockPerDayDataPtr pDayData = data.getCurrentDateData();
	if (pDayData != nullptr && pDayData->getPreviousDateData() && pDayData->getPreviousDateData()->getPreviousDateData()) {
		StockPerDayDataPtr pOneDay = pDayData->getPreviousDateData()->getPreviousDateData();
		StockPerDayDataPtr pTwoDay = pDayData->getPreviousDateData();
		StockPerDayDataPtr pThreeDay = pDayData;

		bool b1 = RiseAndFall().satisfied(*pOneDay);
		bool b2 = pTwoDay->isFall() && pTwoDay->isGreen() && pTwoDay->getVolume() < pOneDay->getVolume();
		bool b3 = pThreeDay->isFall() && pThreeDay->isGreen() && pThreeDay->getVolume() < pTwoDay->getVolume();

		return b1 && b2 && b3;
	}

	return false;
}
