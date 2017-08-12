#pragma once

// https://www.hackerrank.com/challenges/ctci-find-the-running-median

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <iomanip>


using namespace std;

typedef std::priority_queue<int, std::vector<int>, std::greater<int> > MinPriorityQueue;
typedef std::priority_queue<int, std::vector<int>, std::less<int> > MaxPriorityQueue;

void processAddedValue(int value, MinPriorityQueue& maxPartQueue, MaxPriorityQueue& minPartQueue) {
	if (maxPartQueue.empty() || value > maxPartQueue.top())
		maxPartQueue.push(value);
	else
		minPartQueue.push(value);

	const int BALANCE_SIZE_OFFSET = 2; // At least two items difference for balancing needed
	// Balance queues
	while (int(maxPartQueue.size() - minPartQueue.size()) >= BALANCE_SIZE_OFFSET) {
		minPartQueue.push(maxPartQueue.top());
		maxPartQueue.pop();
	}
	while (int(minPartQueue.size() - maxPartQueue.size()) >= BALANCE_SIZE_OFFSET) {
		maxPartQueue.push(minPartQueue.top());
		minPartQueue.pop();
	}
}

double getMedian(MinPriorityQueue& maxPartQueue, MaxPriorityQueue& minPartQueue) {
	auto maxPartCount = maxPartQueue.size();
	auto minPartCount = minPartQueue.size();
	if (maxPartCount == 0 && minPartCount == 0)
		return 0;

	int maxPartTop = maxPartCount > 0 ? maxPartQueue.top() : 0;
	int minPartTop = minPartCount > 0 ? minPartQueue.top() : 0;

	double res = 0;
	if (maxPartCount == minPartCount)
		res = double(maxPartTop + minPartTop) / 2;
	else if (maxPartCount > minPartCount)
		res = maxPartTop;
	else 
		res = minPartTop;

	return res;
}

void findMedians(const std::vector<int> input) {
	MinPriorityQueue minPriorityMaxPartQueue;
	MaxPriorityQueue maxPriorityMinPartQueue;
	std::cout << std::setprecision(2) << std::fixed;
	for (int a_i = 0; a_i < input.size(); ++a_i) {
		int valueAdded = input[a_i];
		processAddedValue(valueAdded, minPriorityMaxPartQueue, maxPriorityMinPartQueue);
		cout <<  getMedian(minPriorityMaxPartQueue, maxPriorityMinPartQueue) << endl;
	}
}
