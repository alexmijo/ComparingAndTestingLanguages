#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include "CppUtilities.cpp"

using namespace std;

struct compareIntPair {
    bool operator()(const pair<int, int>& pair1, const pair<int, int>& pair2) {
        return pair1.first < pair2.first || 
            (pair1.first == pair2.first && pair1.second < pair2.second);
    }
};

int main() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, compareIntPair> maxHeap;
    maxHeap.emplace(pair<int, int>(1, 2));
    maxHeap.emplace(pair<int, int>(2, 2));
    maxHeap.emplace(pair<int, int>(2, 1));
    maxHeap.emplace(pair<int, int>(1, 1));
    for (int i = 0; i < 4; i++) {
        cout << maxHeap.top().first << ", " << maxHeap.top().second << endl;
        maxHeap.pop();
    }

    vector<pair<int, int>> vec(5, pair<int, int>(3, 4));
    vec[3].first = 4;
    vec[2].second = 5;
    sort(vec.begin(), vec.end());
}