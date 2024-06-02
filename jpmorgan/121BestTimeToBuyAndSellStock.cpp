/*
    121. Best Time to Buy and Sell Stock

    You are given an array prices where prices[i] is the price of a given strock 
    on the ith day. 

    You want to maximize your profit by choosing a single day to buy one stock and choosing 
    a different day in the future to sell the stock.

    Return the maximum profit you can achieve from this transaction. If you cannot achieve any 
    profit, return 0

    Example 1:

    Input: prices = [7,1,5,3,6,4]
    Output: 5
    Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

*/

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

class ArrayHashing {
    public:
        int maxProfit(std::vector<int>& prices) {
            int minPrice = prices[0];
            int maxProfit = 0;

            for (int i = 0; i < prices.size(); i++) {
                // If the current price is greater than the previous price, 
                // it means selling on this day can potentially give a profit
                if (prices[i] > prices[i - 1]) {
                    maxProfit = std::max(maxProfit, prices[i] - minPrice);
                } else {
                    // If the current price is not greater than the previous price, 
                    // update minPrice to the current if it is lower than the current minPrice
                    minPrice = std::min(minPrice, prices[i]);
                }
            }
            return maxProfit;
        }
};

int main() {

    std::vector<int> prices = {7,1,5,3,6,4};
    ArrayHashing arrHash;

    std::cout << "Max profit : " << arrHash.maxProfit(prices) << std::endl;

    return 0;
}