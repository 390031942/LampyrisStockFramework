/*
 * File:  StockData.h
 * Brief: �����˹�Ʊÿ������(k������)�����Ʊ��������(ÿ������)�����ݽṹ
 * Author:wushuhong
 * Date�� 20223/12/5
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
    StockDate          m_date;         /* ���� */
                       
    float              m_openPrice;    /* ���̼� */
                       
    float              m_closePrice;   /* ���̼� */
                       
    float              m_highestPrice; /* ��߼� */
                       
    float              m_lowestPrice;  /* ��ͼ� */
                       
    float              m_volume;       /* �ɽ��� */
                       
    float              m_money;        /* �ɽ��� */
                       
    float              m_amplitude;    /* ��� */
                       
    float              m_percentage;   /* �ǵ��� */
                       
    float              m_priceChange;  /* �ǵ��� */
                       
    float              m_turnOverRate; /* ������ */
                       
    PointerType        m_pPrevious;    /* ǰһ������ */
                       
    PointerType        m_pNext;        /* ��һ������ */
                       
public:                
                       StockPerDayData() = default;

                       StockPerDayData(StockPerDayDataPtr prev, StockPerDayDataPtr next);
                       
    virtual           ~StockPerDayData();
                       
    bool               isGapUpOpen() const;   /* ���ո߿� */
                       
    bool               isGapDownOpen() const; /* ���յͿ� */
                       
    bool               isGreen() const; /* �ǲ�����K�� */
                       
    bool               isRed() const; /* �ǲ��Ǻ�K�� */
                       
    bool               isRise() const; /* �ǲ�����K�� */
                       
    bool               isFall() const; /* �ǲ��Ǻ�K�� */
                       
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
