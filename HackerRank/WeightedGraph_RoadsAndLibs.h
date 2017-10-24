#include "stdlib.h"
#include <iostream>
#include <string>
#include "HackerRank/Tries_Contacts.h"
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class LibNetwork
{
public:
  struct Node {
    bool _visited{ false };
    bool _hasConnection{ false };
  };

  LibNetwork(int citiesCount, int roadsCount, long libCost, long roadCost)
    : _citiesCount(citiesCount), _roadsCount(roadsCount), _libCost(libCost), _roadCost(roadCost)
    , _roadNetworks(citiesCount, std::vector<Node>(citiesCount)) { }

  void addRoad(int city1, int city2) {
    auto minCityInd = std::min(city1, city2);
    auto maxCityInd = std::max(city1, city2);
    _roadNetworks[minCityInd - 1][maxCityInd - 1]._hasConnection = true;
  }

  int minBuildCost() {
    if (_libCost <= _roadCost)
      return _libCost * _citiesCount;

    int cost = 0;
    for (int rowInd = 0; rowInd < _citiesCount; ++rowInd) {
      auto& node = _roadNetworks[rowInd][rowInd];
      if (!node._visited) {
        node._visited = true;
        cost += _libCost;
        for (int colInd = rowInd + 1; colInd < _citiesCount; ++colInd)
          processConnectedCities(rowInd, colInd, cost);
      }
    }
    return cost;
  }

private:
  void processConnectedCities(int row, int col, int& cost) {
    auto& node = _roadNetworks[row][col];
    if (node._visited) return;
    node._visited = true;
    if (node._hasConnection) {
      if (!_roadNetworks[col][col]._visited) {
        _roadNetworks[col][col]._visited = true;
        cost += _roadCost;
      }
      int nodeRow = col;
      for (int nodeCol = nodeRow; nodeCol < _citiesCount; ++nodeCol)
        processConnectedCities(nodeRow, nodeCol, cost);
    }
  }

  std::vector<std::vector<Node>> _roadNetworks;
  int _roadsCount{ 0 }, _citiesCount{ 0 };
  long _libCost, _roadCost;
};