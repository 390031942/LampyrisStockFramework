/*
 * File:  StockDataReader.h
 * Brief: 从csv中读取k线数据
 * Author:wushuhong
 * Date： 20223/12/11
*/
#pragma once

// Project Include(s)
#include "Base/StockData.h"

// 3rd-party Include(s)
#include "3rd-party/rapidcsv.h"

// STD Include(s)
#include <filesystem> // C++17

class StockDataReader {
public:
    static StockDataPtr handleSingleFile(const std::string& path);

    static std::vector<StockDataPtr> traverseFolder(const std::string& path);
};