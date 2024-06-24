///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   1353. Maximum Number of Events That Can Be Attended
// 
// You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.
// 
// You can attend an event i at any day d where startTimei <= d <= endTimei. You can only attend one event at any time d.
// 
// Return the maximum number of events you can attend.
// 
//  
// Example 1:
// 
// Input: events = [[1,2],[2,3],[3,4]]
// Output: 3
// Explanation: You can attend all the three events.
// One way to attend them all is as shown.
// Attend the first event on day 1.
// Attend the second event on day 2.
// Attend the third event on day 3.
// 
// Example 2:
// 
// Input: events= [[1,2],[2,3],[3,4],[1,2]]
// Output: 4
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Greedy {
    public:
        int maxEvents(vector<vector<int>>& events) {
            sort(events.begin(), events.end());
            priority_queue<int, vector<int>, greater<int>> minHeap;

            int i = 0, n = events.size(), maxEvents = 0;

            for (int day = 1; day <= 100000; ++day) {
                // Add all events that start on this day to the heap
                while (i < n && events[i][0] == day) {
                    minHeap.push(events[i][0]);
                    ++i;
                }
                // Remove all events that have already ended (end day < current day)
                while (!minHeap.empty() && minHeap.top() < day) {
                    minHeap.pop();
                }
                // Attend the event that ends the earliest (if there is any)
                if (!minHeap.empty()) {
                    minHeap.pop();
                    ++maxEvents;
                }
            }
            return maxEvents;
        }

};

int main() {

    Greedy gd;

    vector<vector<int>> A = {{1, 2}, {2, 3}, {3, 4}};

    cout << gd.maxEvents(A) << endl; 


    return 0;
}