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

// Project Include(s)
#include "Descriptor/RiseAndFall.h"
#include "Descriptor/ConsecutiveRed.h"
#include "Descriptor/ConsecutiveRedAndFall.h"
#include "Descriptor/GapUpOpenAndFall.h"
#include "Descriptor/BigRedAndTwoGreen.h"

#include "Core/AnalyzerEngine.h"
#include "Base/StockDataReader.h"

void printResult(std::vector<StockDataPtr>& result) {
	for (StockDataPtr ptr : result) {
		std::cout << ptr->getFileName() << std::endl;
	}
}

int main() {
    StockDataReader reader;

    std::vector<StockDataPtr> stockList = reader.traverseFolder("C:\\Users\\wsh39\\Desktop\\Working\\LampyrisStockAnalyzer\\Dataset");
    AnalyzerEngine analyzerEngine(stockList);

    {
		std::cout << "冲高回落:" << std::endl;
		RiseAndFall descriptor;
		std::vector<StockDataPtr> result;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
    }

	{
		std::cout << "三连阳" << std::endl;
		ConsecutiveRed descriptor;
		std::vector<StockDataPtr> result;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
	}

	{
		std::cout << "三连阳回落" << std::endl;
		ConsecutiveRedAndFall descriptor;
		std::vector<StockDataPtr> result;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
	}

	{
		std::cout << "跳空高开回落" << std::endl;
		GapUpOpenAndFall descriptor;
		std::vector<StockDataPtr> result;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
	}

	{
		std::cout << "一根大阳线后缩量两连阴" << std::endl;
		BigRedAndTwoGreen descriptor;
		std::vector<StockDataPtr> result;
		analyzerEngine.filter(result, descriptor);
		printResult(result);
	}
    return 0;
}