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

void mergeHalves(vector<int>& source, vector<int>& temp, int leftStart, int rightEnd, int& inversionsCount) {
	int leftEnd = (leftStart + rightEnd) / 2;
	int rightStart = leftEnd + 1;
	
	int index = leftStart;
	int left = leftStart;
	int right = rightStart;

	while (left <= leftEnd && right <= rightEnd) {
		if (source[left] <= source[right]) {
			temp[index] = source[left];
			++left;
		}
		else {
			temp[index] = source[right];
			inversionsCount += (leftEnd - left + 1);
			++right;
		}
		++index;
	}

	copy(begin(source) + left, begin(source) + leftEnd + 1, begin(temp) + index);
	copy(begin(source) + right, begin(source) + rightEnd + 1, begin(temp) + index);
	copy(begin(temp) + leftStart, begin(temp) + rightEnd + 1, begin(source) + leftStart);
}

void mergeSort(vector<int>& arr, vector<int>& temp, int start, int end, int& inversionsCount) {
	if (start >= end) {
		return;
	}
	int mid = (start + end) / 2;
	mergeSort(arr, temp, start, mid, inversionsCount);
	mergeSort(arr, temp, mid+1, end, inversionsCount);
	mergeHalves(arr, temp, start, end, inversionsCount);
}

long countInversions(vector<int> arr) {
	int inversionsCount = 0;
	size_t count = arr.size();
	if (count > 0) {
		vector<int> temp(count);
		mergeSort(arr, temp, 0, (int)count - 1, inversionsCount);
	}
	return inversionsCount;
}
