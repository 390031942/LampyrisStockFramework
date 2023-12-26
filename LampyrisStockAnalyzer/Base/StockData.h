/*
 * File:  StockData.h
 * Brief: 定义了股票每日数据(k线数据)，与股票行情数据(每日数据)的数据结构
 * Author:wushuhong
 * Date： 20223/12/5
*/
#pragma once

// STD Include(s)
#include <vector>
#include <string>
#include <memory> // std::shared_ptr
#include <sstream>
#include <iomanip>
#include <chrono>

class StockPerDayData;
class StockData;

typedef std::shared_ptr<StockPerDayData> StockPerDayDataPtr;
typedef std::shared_ptr<StockData> StockDataPtr;
typedef std::chrono::year_month_day StockDate;

class StockPerDayData {
    typedef StockPerDayDataPtr PointerType;
private:
    StockDate          m_date;         /* 日期 */
                       
    float              m_openPrice;    /* 开盘价 */
                       
    float              m_closePrice;   /* 收盘价 */
                       
    float              m_highestPrice; /* 最高价 */
                       
    float              m_lowestPrice;  /* 最低价 */
                       
    float              m_volume;       /* 成交量 */
                       
    float              m_money;        /* 成交额 */
                       
    float              m_amplitude;    /* 振幅 */
                       
    float              m_percentage;   /* 涨跌幅 */
                       
    float              m_priceChange;  /* 涨跌额 */
                       
    float              m_turnOverRate; /* 换手率 */
                       
    PointerType        m_pPrevious;    /* 前一天数据 */
                       
    PointerType        m_pNext;        /* 后一天数据 */
                       
public:                
                       StockPerDayData() = default;

                       StockPerDayData(StockPerDayDataPtr prev, StockPerDayDataPtr next);
                       
    virtual           ~StockPerDayData();
                       
    bool               isGapUpOpen() const;   /* 跳空高开 */
                       
    bool               isGapDownOpen() const; /* 跳空低开 */
                       
    bool               isGreen() const; /* 是不是绿K线 */
                       
    bool               isRed() const; /* 是不是红K线 */
                       
    bool               isRise() const; /* 是不是绿K线 */
                       
    bool               isFall() const; /* 是不是红K线 */
                       
    inline StockDate   getDate() const { return this->m_date; };
                       
    inline float       getOpenPrice() const{ return this->m_openPrice; };
                       
    inline float       getClosePrice() const { return this->m_closePrice; };
                       
    inline float       getHighestPrice() const { return this->m_highestPrice; };
                       
    inline float       getLowestPrice() const { return this->m_lowestPrice; };
                       
    inline float       getVolume() const { return this->m_volume; };
                       
    inline float       getMoney() const { return this->m_money; };
                       
    inline float       getAmplitude() const { return this->m_amplitude; };
                       
    inline float       getPercentage() const { return this->m_percentage; };
                       
    inline float       getPriceChange() const { return this->m_priceChange; };
                       
    inline float       getTurnOverRate() const { return this->m_turnOverRate; };
                       
    inline float       getLastClosePrice() const { return this->m_pPrevious->m_closePrice; }

    inline PointerType getPreviousDateData(int day = 1) const { 
        if (day == 1) {
            return this->m_pPrevious;
        }
        PointerType p = this->m_pPrevious;
        while (--day >= 0) {
            p = p->getPreviousDateData();
            if (!p) {
                return nullptr;
            }
        }
        return p; 
    }

    inline PointerType getNextDateData() const { return this->m_pNext; }

    friend class StockDataReader;
};

class StockData {
private:
	std::string m_name;
	std::string m_fileName;
    std::vector<StockPerDayDataPtr> m_stockPerDayData;
public:
    const StockPerDayDataPtr getCurrentDateData() const {
        return !m_stockPerDayData.empty() ? m_stockPerDayData.back() : nullptr;
    }

    const std::string& getName() const {
        return this->m_name;
    }

	const std::string& getFileName() const {
		return this->m_fileName;
	}


    friend class StockDataReader;
};
