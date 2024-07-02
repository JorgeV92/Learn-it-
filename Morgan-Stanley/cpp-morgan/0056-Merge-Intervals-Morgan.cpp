#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> mergedIntervals; 

    mergedIntervals.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); i++) {
        vector<int>& lastInteral = mergedIntervals.back();

        if (intervals[i][0] <= lastInteral[1]) {
            lastInteral[1] = max(lastInteral[1], intervals[i][1]);
        } else {
            mergedIntervals.push_back(intervals[i]);
        }
    }

    return mergedIntervals;
}