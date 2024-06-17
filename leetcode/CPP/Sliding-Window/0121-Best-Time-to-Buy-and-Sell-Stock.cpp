/*
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
*/

#include <iostream>
#include <vector>

class SlidingWindow {
    public:
        int maxProfit(std::vector<int>& prices) {
            if (prices.empty()) return 0;

            // Initialize the minimum price to the first element
            int min_price_so_far = prices[0];
            // Initialize the maximum profit to 0
            int max_profit_so_far = 0;

            // Iterate through the prices starting from the second element
            for (int i = 1; i < prices.size(); ++i) {
                // Calculate the potential profit if selling on the current day
                int potential_profit = prices[i] - min_price_so_far;

                // Update the maximum profit encountered so far
                max_profit_so_far = std::max(max_profit_so_far, potential_profit);

                // Update the minimum price encountered so far
                min_price_so_far = std::min(min_price_so_far, prices[i]);
            }

            // Return the maximum profit found
            return max_profit_so_far;
        }
};

int main() {
    SlidingWindow sw;

    // Example 1
    std::vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    std::cout << "Max Profit (Example 1): " << sw.maxProfit(prices1) << std::endl; // Output: 5

    // Example 2
    std::vector<int> prices2 = {7, 6, 4, 3, 1};
    std::cout << "Max Profit (Example 2): " << sw.maxProfit(prices2) << std::endl; // Output: 0

    return 0;
}