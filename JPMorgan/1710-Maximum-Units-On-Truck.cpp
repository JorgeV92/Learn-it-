/*
    1710. Maximum Units on a Truck   (Easy)

    You are assigned to put some amount of boxes onto one truck. You are given a 2D array boxTypes,
    where boxTypes[i] = [numberOfBoxes, numberOfUnitsPerBox]:
        - numberOfBoxes_i is the number of boxes of type i. 
        - numberOfUnitsPerBox_i is the number of units in each box of the type i.

    You are also given an integer truckSize, which is the maximum number of boxes that can be put 
    on the truck. You can choose any boxes to put on the truck as long as the number of boxes does not 
    exceed truckSize.

    Return the maximum total number of units that can be put on the truck.

    Example 1:

    Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
    Output: 8
    Explanation: There are:
    - 1 box of the first type that contains 3 units.
    - 2 boxes of the second type that contain 2 units each.
    - 3 boxes of the third type that contain 1 unit each.
    You can take all the boxes of the first and second types, and one box of the third type.
    The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1) = 8.    
*/
#include <iostream>
#include <vector>
#include <algorithm>

class Greedy {
    public:
        int maximumUnits(std::vector<std::vector<int>>& boxTypes, int truckSize) {
            // Sort the box types by the number of units per box in descending order 
            std::sort(boxTypes.begin(), boxTypes.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
                return a[1] > b[1];
            });

            int totalUnits = 0;

            for (const auto& box : boxTypes) {
                int numberOfBoxes = box[0];
                int unitsPerBox = box[1];

                if (truckSize >= numberOfBoxes) {
                    // If the truck can carray all boxes of this type 
                    totalUnits += numberOfBoxes * unitsPerBox;
                    truckSize -= numberOfBoxes;
                } else {
                    // If the truck can only carry some of the boxes of this type 
                    totalUnits += truckSize * unitsPerBox;
                    break;  // Truck is full
                }
            }
            return totalUnits;
        }
};

int main() {
    std::vector<std::vector<int>> boxTypes {{1, 3}, {2, 2}, {3, 1}};
    int truckSize = 4;

    Greedy gd;
    int result = gd.maximumUnits(boxTypes, truckSize);
    std::cout << "Maximum Units on a truck : " << result << std::endl;

    std::vector<std::vector<int>> boxTypes2 {{5, 10}, {2, 5}, {4, 7}, {3, 9}};
    int truckSize2 = 10;

    int result2 = gd.maximumUnits(boxTypes2, truckSize2);

    std::cout << "Maximum Units on a truck #2: " << result2 << std::endl;
    
    return 0;
}