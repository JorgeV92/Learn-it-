'''
 _______        _____ ______  _____ __   _  ______      _  _  _ _____ __   _ ______   _____  _  _  _     
 |______ |        |   |     \   |   | \  | |  ____      |  |  |   |   | \  | |     \ |     | |  |  |     
 ______| |_____ __|__ |_____/ __|__ |  \_| |_____|      |__|__| __|__ |  \_| |_____/ |_____| |__|__|     
                                                                                                   
    0121. Best Time to Buy and Sell Stock   (Easy)

    You are given an array prices where prices[i] is the proce of a given stock in the ith 
    day. 

    You want to maximize your profit by choosing a single day to buy one stock and choosing a 
    different day in the future to sell that stock.

    Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, 
    return 0.

    Example 1:

    Input: prices = [7,1,5,3,6,4]
    Output: 5
    Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.


    Example 2:

    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transactions are done and the max profit = 0.
'''

from typing import List

class SlidingWindow:
    def max_profit(self, prices: List[int]) -> int:
        if not prices:
            return 0
        
        min_price_so_far = prices[0]
        max_profit_so_far = 0
        
        for price in prices[1:]:
            potential_price = price - min_price_so_far
            max_profit_so_far = max(max_profit_so_far, potential_price)
            min_price_so_far = min(min_price_so_far, price)
        return max_profit_so_far
    
if __name__ == "__main__":
    sw = SlidingWindow()

    # Example 1
    prices1 = [7, 1, 5, 3, 6, 4]
    print(f"Max Profit (Example 1): {sw.max_profit(prices1)}")  # Output: 5

    # Example 2
    prices2 = [7, 6, 4, 3, 1]
    print(f"Max Profit (Example 2): {sw.max_profit(prices2)}")  # Output: 0
        