/*
 * File:  RiseAndFall.cpp
 * Brief: ��߻���/�γ�(��)��Ӱ��
 * Author:wushuhong
 * Date�� 20223/12/5
*/
#include "RiseAndFall.h"

bool RiseAndFall::satisfied(const StockData& data) const {
    if (data.getFileName().find("����˹��") > 0) {
        int a = 1;
    }

    auto pDateData = data.getCurrentDateData();
    return satisfied(*pDateData);
}

bool RiseAndFall::satisfied(const StockPerDayData& data) const {
    // ����1�� ������ > 5%
    bool condition1 = data.getTurnOverRate() > 5.00f;

    // ����2�� ��� > 5%
    bool condition2 = data.getAmplitude() > 5.00f;

    // ����3�� k�����ǲ��Һ�
    bool condition3 = data.isRise() && data.isRed();

    // ����4�� ����Ƿ�/�����Ƿ�  ������1.5��2.0֮��
    float highPercentage = 100.0f * (data.getHighestPrice() / data.getLastClosePrice() - 1);
    float openPercentage = 100.0f * (data.getOpenPrice() / data.getLastClosePrice() - 1);
    float percentage = data.getPercentage();
    float diff = highPercentage - percentage;
    float diff2 = percentage - openPercentage;
    bool condition4 = diff > 1.0f && diff2 > 2.f;

    return condition1 && condition2 && condition3 && condition4;
}
