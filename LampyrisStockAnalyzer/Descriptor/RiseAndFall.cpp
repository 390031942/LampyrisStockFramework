/*
 * File:  RiseAndFall.cpp
 * Brief: 冲高回落/形成(长)上影线
 * Author:wushuhong
 * Date： 20223/12/5
*/
#include "RiseAndFall.h"

bool RiseAndFall::satisfied(const StockData& data) const {
    if (data.getFileName().find("罗普斯金") > 0) {
        int a = 1;
    }

    auto pDateData = data.getCurrentDateData();
    return satisfied(*pDateData);
}

bool RiseAndFall::satisfied(const StockPerDayData& data) const {
    // 条件1： 换手率 > 5%
    bool condition1 = data.getTurnOverRate() > 5.00f;

    // 条件2： 振幅 > 5%
    bool condition2 = data.getAmplitude() > 5.00f;

    // 条件3： k线收涨并且红
    bool condition3 = data.isRise() && data.isRed();

    // 条件4： 最高涨幅/收盘涨幅  比例在1.5与2.0之间
    float highPercentage = 100.0f * (data.getHighestPrice() / data.getLastClosePrice() - 1);
    float openPercentage = 100.0f * (data.getOpenPrice() / data.getLastClosePrice() - 1);
    float percentage = data.getPercentage();
    float diff = highPercentage - percentage;
    float diff2 = percentage - openPercentage;
    bool condition4 = diff > 1.0f && diff2 > 2.f;

    return condition1 && condition2 && condition3 && condition4;
}
