#
# File:  main.py
# Brief: 提取所有市场数据到csv表格
# Author:wushuhong
# Date： 2023/12/5
#

# -*- coding: utf-8 -*-

import efinance as ef
import warnings
import time
import os

# 禁用警告
warnings.filterwarnings('ignore')

# 获取当前文件的绝对路径
current_file_path = os.path.realpath(__file__)

# 获取当前文件的父目录
current_dir = os.path.dirname(current_file_path)

# 设置工作目录为当前文件的父目录
os.chdir(current_dir)

exportDirPath = os.path.join(current_dir,"Dataset")
exportFilePath = os.path.join(exportDirPath,"{}_{}.csv")
header=["股票名称","股票代码","日期","开盘价","收盘价","最高价","最低价","成交量","成交额","振幅","涨跌幅","涨跌额","换手率"]

if not os.path.exists(exportDirPath):
    os.makedirs(exportDirPath)

class PerDayDataEnum():
    # 股票名称
    STOCK_NAME = 0
    # 股票代码
    STOCK_CODE = 1
    # 日期
    DATE = 2,
    # 开盘价
    OPEN_PRICE = 3
    # 收盘价
    CLOSE_PRICE = 4
    # 最高价
    HIGHEST_PRICE = 5
    # 最低价
    LOWEREST_PRICE = 6
    # 成交量
    VOLUME = 7
    # 成交额
    MONEY = 8
    # 振幅
    AMPLITUDE = 9
    # 涨跌幅
    PERCENTAGE = 10
    # 涨跌额
    PRICE_CHANGE = 11
    # 换手率
    TURNOVER_RATE = 12

def analyzeSingle(stock_code,begin,end):
    # 获取股票日 K 数据
    df = ef.stock.get_quote_history(stock_code, beg=begin, end=end)

    # 日K数据 -> 列表
    dataList = list(df.iterrows())

    if(len(dataList) != 3):
        return

    dayOne   = dataList[0][1]
    dayTwo   = dataList[1][1]
    dayThree = dataList[2][1]
                                                                                         
    if(dayOne[PerDayDataEnum.PERCENTAGE] > 5.00 and (dayTwo[PerDayDataEnums.PERCENTAGE] + dayThree[PerDayDataEnum.PERCENTAGE]) < -5.00):
        print(dayThree[PerDayDataEnum.STOCK_NAME] + "," + str(dayThree[PerDayDataEnum.STOCK_CODE]))

def exportToCSV(stock_code,begin,end):
    # 获取股票日 K 数据
    df = ef.stock.get_quote_history(stock_code, beg=begin, end=end)
    dataList = list(df.iterrows())
    if(len(dataList) > 0):
        df.to_csv(str.format(exportFilePath,str(dataList[0][1][PerDayDataEnum.STOCK_CODE]),dataList[0][1][PerDayDataEnum.STOCK_NAME]), header = header, index=False)

def main():
    # 获取沪深全市场股票整体状况
    all_stock_data = ef.stock.get_realtime_quotes()

    # 所有沪深主板的股票列表(不包含N，ST,*ST股)
    all_stock_code_list = []

    for index, row in all_stock_data.iterrows():
        code = row[0]
        name = row[1]
        code_str_prefix = str(code)[:2]

        # 沪深主板的代码规则: 60 或 00开头
        if((code_str_prefix == "60" or code_str_prefix == "00") and not ("N" in name or "ST" in name or "*ST" in name or "PT" in name or "退" in name)):
            all_stock_code_list.append(code)

        all_stock_code_list.sort()
     
    # 开始日期(1990年有的股市)
    beg = '20231101'
    # 结束日期
    end = '20231226'

    totalLength = len(all_stock_code_list)
    current = 0

    # 获取当前时间
    start_time = time.time()  

    for code in all_stock_code_list:
        # analyzeSingle(code,beg,end)
        exportToCSV(code,beg,end)
        current = current + 1
        print(str.format("Progress:{} / {}",current,totalLength))

    # 获取当前时间
    end_time = time.time() 
    # 计算执行时间
    execution_time = end_time - start_time  
    print(str.format("导出{}支股票的数据，总共耗时{} 秒", totalLength,execution_time))

if __name__ == "__main__":
    main()