/*
    0322. Coin Change (Medium)

    You are given an integer array coins representing of different denominations and an integer
    amount representing a total amount of money.

    Return the fewest number of coins that you need to make up that amount. If that amount of money 
    cannot be made up by any combination of the coins, return -1.


    Example 1:

    Input: coins = [1,2,5], amount = 11
    Output: 3
    Explanation: 11 = 5 + 5 + 1

    Example 2:

    Input: coins = [2], amount = 3
    Output: -1
    Example 3:

    Input: coins = [1], amount = 0
    Output: 0
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class DynamicProgramming1D {
    public:
        int coinChange(std::vector<int>& coins, int amount) {
            // if amount is 0, no coins are needed
            if (amount == 0) return 0;

            // array with a large value (INT_MAX)
            std::vector<int> minCoins(amount + 1, INT_MAX);
            // Base case: 0 coins are needed to make amount 0
            minCoins[0] = 0; 

            // iterate over all the amount from 1 to amount 
            for (int i = 1; i <= amount; i++) {
                // check each coin 
                for (int coin : coins) {
                    // if the coin is less than or equal to the current amount 
                    if (coin <= i && minCoins[i - coin] != INT_MAX) {
                        // Update the minCoins array with the minimum number of coins needed
                        minCoins[i] = std::min(minCoins[i], minCoins[i - coin] + 1);
                    }
                }
            }
            return minCoins[amount] == INT_MAX ? -1 : minCoins[amount];
        }
};

int main() {
    DynamicProgramming1D dp1d;
    
    std::vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    std::cout << "Fewest coins needed for amount " << amount1 << ": " << dp1d.coinChange(coins1, amount1) << std::endl;
    // Output: 3 (Explanation: 11 = 5 + 5 + 1)

    std::vector<int> coins2 = {2};
    int amount2 = 3;
    std::cout << "Fewest coins needed for amount " << amount2 << ": " << dp1d.coinChange(coins2, amount2) << std::endl;
    // Output: -1 (Explanation: Cannot make up amount 3 with only coin 2)

    std::vector<int> coins3 = {1};
    int amount3 = 0;
    std::cout << "Fewest coins needed for amount " << amount3 << ": " << dp1d.coinChange(coins3, amount3) << std::endl;
    // Output: 0 (Explanation: No coins are needed for amount 0)
    
    std::vector<int> coins4 = {1, 2, 5};
    int amount4 = 7;
    std::cout << "Fewest coins needed for amount " << amount4 << ": " << dp1d.coinChange(coins4, amount4) << std::endl;
    // Output: 2 (Explanation: 7 = 5 + 2)
    
    return 0;
}