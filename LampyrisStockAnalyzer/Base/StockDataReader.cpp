#include "StockDataReader.h"

StockDataPtr StockDataReader::handleSingleFile(const std::string& path) {
    // 从CSV文件中读取数据
    rapidcsv::Document readDoc(path);

    StockDataPtr pStockData = std::make_shared<StockData>();
    StockPerDayDataPtr pPrevious = nullptr;

    pStockData->m_stockPerDayData.reserve(readDoc.GetRowCount());
    pStockData->m_fileName = std::filesystem::path(path).filename().string();

    // 获取并打印所有行数据
    for (size_t i = 0; i < readDoc.GetRowCount(); i++) {
        std::vector<std::string> row = readDoc.GetRow<std::string>(i);
        StockPerDayDataPtr pCurrent = std::make_shared<StockPerDayData>();

		pStockData->m_name = row[0];

        // 日期
        std::istringstream ss(row[2]);
        std::tm tm = {};
        ss >> std::get_time(&tm, "%Y%m%d");

        std::chrono::year_month_day date(
            std::chrono::year(tm.tm_year + 1900),
            std::chrono::month(tm.tm_mon + 1),
            std::chrono::day(tm.tm_mday)
        );

        pCurrent->m_date = date;

        // 价格
        pCurrent->m_openPrice = std::stof(row[3]);
        pCurrent->m_closePrice = std::stof(row[4]);
        pCurrent->m_highestPrice = std::stof(row[5]);
        pCurrent->m_lowestPrice = std::stof(row[6]);

        // 量能/金额
        pCurrent->m_volume = std::stof(row[7]);
        pCurrent->m_money = std::stof(row[8]);

        // 振幅
        pCurrent->m_amplitude = std::stof(row[9]);

        // 涨跌幅/涨跌额
        pCurrent->m_percentage = std::stof(row[10]);
        pCurrent->m_priceChange = std::stof(row[11]);

        // 换手率
        pCurrent->m_turnOverRate = std::stof(row[12]);

        if (pPrevious != nullptr) {
            pPrevious->m_pNext = pCurrent;
            pCurrent->m_pPrevious = pPrevious;
        }

        pPrevious = pCurrent;
        pStockData->m_stockPerDayData.push_back(pCurrent);
    }

    return pStockData;
}

std::vector<StockDataPtr> StockDataReader::traverseFolder(const std::string& path) {
    std::vector<StockDataPtr> stockDataList;
    std::filesystem::path cwd = path;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(cwd)) {
        if (entry.path().extension() == ".csv" && entry.path().filename().string().find("C") == std::string::npos) {
            auto pStockData = handleSingleFile(entry.path().string());
            stockDataList.push_back(pStockData);
        }
    }

    return stockDataList;
}
