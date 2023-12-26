/*
 * File:  main.cpp
 * Brief: LampyrisStockAnalyzer入口函数所在文件
 * Author:wushuhong
 * Date： 2023/12/5
*/

#if _MSVC_LANG < 201703L
 #error The MSVC compiler must enable C++17 features to compile this program.
#endif // !  _MSVC_LANG < 201703L

// STD Include(s)
#include <iostream>
#include <vector>
#include <string>
#include <memory> // std::shared_ptr
#include <format> // C++ 20

// Project Include(s)
#include "Descriptor/RiseAndFall.h"
#include "Descriptor/ConsecutiveRed.h"
#include "Descriptor/ConsecutiveRedAndFall.h"
#include "Descriptor/GapUpOpenAndFall.h"
#include "Descriptor/BigRedAndTwoGreen.h"

#include "Core/AnalyzerEngine.h"
#include "Base/StockDataReader.h"
#include <unordered_set>

static void printResult(const std::vector<StockDataPtr>& result) {
	for (StockDataPtr ptr : result) {
		std::cout << ptr->getFileName() << std::endl;
	}
}

static std::string generatePythonListCode(const std::unordered_set<std::string>& stockCodeSet) {
	std::string result = "[";
	if (!stockCodeSet.empty()) {
		for (auto code : stockCodeSet) {
			result += std::format("'{}',", code);
		}
	}
	result += "]";

	return result;
}

static void appendNeedWatchStockCode(const std::vector<StockDataPtr>& result, std::unordered_set<std::string>& stockCodeSet) {
	for (StockDataPtr ptr : result) {
		stockCodeSet.insert(ptr->getCode());
	}
}

int main(int argc,char** argv) {
	if (argc == 1) {
		std::cout << "用法: LampyrisStockAnalyzer.exe 数据集目录" << std::endl;
		return -1;
	}

	const char* path = argv[1];
	if (!(std::filesystem::exists(path) && std::filesystem::is_directory(path))) {
		std::cout << "输入数据集文件路径无效，请检查!" << std::endl;
		return -1;
	}

	/* 递归遍历包含csv文件的文件夹，得到股票历史数据 */
    StockDataReader reader;
    std::vector<StockDataPtr> stockList = reader.traverseFolder(argv[1]);

	/* 从已有选股规则中得到的股票代码集合 */
	std::unordered_set<std::string> needWatchSet;

	/* 从单个规则中选出来的股票数据 */
	std::vector<StockDataPtr> result;

	AnalyzerEngine analyzerEngine(stockList);
    {
		result.clear();
		std::cout << "冲高回落:" << std::endl;
		RiseAndFall descriptor;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
		appendNeedWatchStockCode(result, needWatchSet);
    }

	{
		result.clear();
		std::cout << "三连阳" << std::endl;
		ConsecutiveRed descriptor;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
		appendNeedWatchStockCode(result, needWatchSet);
	}

	{
		result.clear();
		std::cout << "三连阳回落" << std::endl;
		ConsecutiveRedAndFall descriptor;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
		appendNeedWatchStockCode(result, needWatchSet);
	}

	{
		result.clear();
		std::cout << "跳空高开回落" << std::endl;
		GapUpOpenAndFall descriptor;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
		appendNeedWatchStockCode(result, needWatchSet);
	}

	{
		result.clear();
		std::cout << "一根大阳线后缩量两连阴" << std::endl;
		BigRedAndTwoGreen descriptor;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
		appendNeedWatchStockCode(result, needWatchSet);
	}

	std::cout << "Python Code:\n" << generatePythonListCode(needWatchSet) << std::endl;
    return 0;
}