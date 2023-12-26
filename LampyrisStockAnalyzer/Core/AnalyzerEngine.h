/*
 * File:  AnalyzerEngine.h
 * Brief: 封装了一套K线走势分析函数，可以根据区间走势进行股票的筛选
 * Author:wushuhong
 * Date： 20223/12/11
*/
#pragma once

// Project Include(s)
#include "Base/StockDescriptor.h"

// STD Include(s)
#include <functional>

template<typename T>
concept BasicType = std::is_fundamental_v<T>;

class AnalyzerEngine {
private:
	std::vector<StockDataPtr> m_stockData;
public:
	AnalyzerEngine(std::vector<StockDataPtr>& stockData) {
		m_stockData = stockData;
	}

	template<class Descriptor>
	void filter(std::vector<StockDataPtr>& result,const Descriptor& descriptor) {
		for (StockDataPtr ptr : m_stockData) {
			if (ptr->getFileName().find("广州浪奇") != std::string::npos) {
				int a = 0;  
			}
			if (descriptor.satisfied(*ptr)) {
				result.push_back(ptr);
			}
		}
	}

	template<class T,class ...Args>
	void filter(std::vector<StockDataPtr>& result,const T& descriptor,Args&&... args) {
		filter(result,descriptor,args...);
	}

	template<class ReturnType> requires BasicType<ReturnType>
	void max(std::vector<StockDataPtr>& result, std::function<ReturnType(StockDataPtr)> callback) {
		ReturnType returnType = ReturnType();
		for (StockDataPtr ptr : m_stockData) {
			returnType = std::max(returnType, callback(ptr));
		}
		return returnType;
	}

	template<class ReturnType> requires BasicType<ReturnType>
	void min(std::vector<StockDataPtr>& result, std::function<ReturnType(StockDataPtr)> callback) {
		ReturnType returnType = ReturnType();
		for (StockDataPtr ptr : m_stockData) {
			returnType = std::min(returnType, callback(ptr));
		}
		return returnType;
	}

	template<class ReturnType> requires BasicType<ReturnType>
	void sum(std::vector<StockDataPtr>& result, std::function<ReturnType(StockDataPtr)> callback) {
		ReturnType returnType = ReturnType();
		for (StockDataPtr ptr : m_stockData) {
			returnType += callback(ptr);
		}
		return returnType;
	}

	int count(std::vector<StockDataPtr>& result, std::function<bool(StockDataPtr)> callback) {
		int count = 0;
		for (StockDataPtr ptr : m_stockData) {
			count += callback(ptr) ? 1:0;
		}
		return count;
	}
};
