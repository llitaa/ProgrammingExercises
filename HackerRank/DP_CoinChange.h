#pragma once

// https://www.hackerrank.com/challenges/ctci-coin-change

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

typedef vector<vector<long long>> MemoizationMap;

bool coinExists(const set<int>& coins, int value) {
	return coins.find(value) != end(coins);
} 

long long make_change(vector<int> coins, int money) {
	set<int> coinsSet(begin(coins), end(coins));
	int maxCoin = coinsSet.empty() ? 0 : *coinsSet.rbegin();

	MemoizationMap memoMap(maxCoin+1, vector<long long>(money+1, 0));
	memoMap[0][0] = 1;
	
	for (long i = 1; i <= maxCoin; ++i) {
		for (long j = 0; j <= money; ++j) {
			if (i == 0 && j == 0) {
				memoMap[i][j] = 1;
				continue;
			}
			if (i > j || !coinExists(coinsSet, i)) {
				memoMap[i][j] = memoMap[i - 1][j];
			}
			else {
				memoMap[i][j] = memoMap[i - 1][j] + memoMap[i][j - i];
			}
		}
	}
	return memoMap[maxCoin][money];
}
