#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

class LibNetwork
{
public:
	LibNetwork(int citiesCount, int roadsCount, long libCost, long roadCost)
		:_cityConnections(citiesCount), _visited(citiesCount, false), _libCost(libCost), _roadCost(roadCost) {}

	void addRoad(int city1, int city2) {
		_cityConnections[city1 - 1].insert(city2 - 1);
		_cityConnections[city2 - 1].insert(city1 - 1);
	}

	long minBuildCost() {
		if (_libCost <= _roadCost)
			return _libCost*_cityConnections.size();

		long cost = 0;
		for (size_t i = 0; i < _cityConnections.size(); ++i) {
			if (!_visited[i]) {
				cost += _libCost;
				_visited[i] = true;
				processAdjacentCities(i, cost);
			}
		}
		return cost;
	}

private:
	void proccessCity(int cityInd, long& cost) {
		if (!_visited[cityInd]) {
			_visited[cityInd] = true;
			cost += _roadCost;
			processAdjacentCities(cityInd, cost);
		}
	}

	void processAdjacentCities(int cityInd, long& cost) {
		for (auto adjCityInd = begin(_cityConnections[cityInd]); adjCityInd != end(_cityConnections[cityInd]); ++adjCityInd)
			proccessCity(*adjCityInd, cost);
	}

	vector<unordered_set<int>> _cityConnections;
	vector<int> _visited;
	long _libCost, _roadCost;
};