# 导入 efinance 库
from time import sleep
import warnings
import efinance as ef
import os

warnings.filterwarnings('ignore')

# 股票代码
stock_code = ['上证指数','399001','605378','600610','002671','002333','603315']

def printSingle(stock_code):
    df = ef.stock.get_quote_history(stock_code, klt=1)
    df = list(df.iterrows())

    if(len(df) > 0):
        openPrice = df[0][1][4] - df[0][1][11]

        stockName = df[0][1][0]
        currentPercentage,riseSpeed = 0,0

        currentPercentage = (df[len(df) - 1][1][4] - openPrice) / openPrice * 100

        if(len(df) <= 5):
            riseSpeed = currentPercentage
        else:
            fiveMinPrice = df[len(df) - 4][1][4]
            currentPrice = df[len(df) - 1][1][4]

            riseSpeed = (currentPrice - fiveMinPrice) / fiveMinPrice * 100

        currentPercentage = round(currentPercentage,2)
        riseSpeed = round(riseSpeed,2)
        
        stockNameStr = stockName
        if(len(stockNameStr) < 4):
            stockNameStr = stockNameStr + "  "

        currentPercentageStr = str(currentPercentage) + "%"
        if(len(currentPercentageStr) == 4):
            currentPercentageStr = currentPercentageStr + "  "
        elif(len(currentPercentageStr) == 5):
            currentPercentageStr = currentPercentageStr + " "  

      
        return stockNameStr + "         " + currentPercentageStr + "         " + str(riseSpeed) + "%" + "        " + str(currentPrice)

    return stock_code

if __name__ == "__main__":
    while(True):
        result = ""
        for name in stock_code:
            result = result + printSingle(name) + "\n"
        os.system("cls")
        print(result)
        sleep(3)
        



