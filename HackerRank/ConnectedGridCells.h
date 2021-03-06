#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>


// https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid

// Test commit from other machine

bool canBeConnected(int value)
{
	return value != 0;
}

//8
//9
//0 1 0 0 0 0 1 1 0
//1 1 0 0 1 0 0 0 1
//0 0 0 0 1 0 1 0 0
//0 1 1 1 0 1 0 1 1
//0 1 1 1 0 0 1 1 0
//0 1 0 1 1 0 1 1 0
//0 1 0 0 1 1 0 1 1
//1 0 1 1 1 1 0 0 0
//res 29

int findConnectedGridCellsMaxCount()
{
	// Read input data
	int row = 0, column = 0;
	std::cin >> row;
	std::cin >> column;
	
	if (row <= 0 || row >= 10 || column <= 0 || column >= 10)
		return -1;

	std::vector<std::vector<int>> sourceData(row);
	for (int i = 0; i < row; ++i)
	{
		std::vector<int> rowData(column);
		for (int j = 0; j < column; ++j)
		{
			std::cin >> rowData[j];
		}
		sourceData[i] = std::move(rowData);
	}

	typedef std::set<std::pair<int, int>> ConnectionCluster;
	std::vector<ConnectionCluster> connectionClusters;

	auto clusterFinder = [&connectionClusters](int elementRow, int elementCol, int& resClusterIndex) -> bool
	{
		resClusterIndex = -1;
		auto it = std::find_if(begin(connectionClusters), end(connectionClusters), [&](const ConnectionCluster& cluster) 
		{
			return cluster.find({ elementRow , elementCol }) != end(cluster);
		});
		bool success = it != end(connectionClusters);
		if (success)
			resClusterIndex = std::distance(begin(connectionClusters), it);
		
		return success;
	};
	
  // Merges clusters, returns merged cluster index
  auto mergeClusters = [&](std::set<int> connectedClusterIndices) -> int
  {
    int res = -1;
    auto clustersCount = connectedClusterIndices.size();
    if (clustersCount == 0) return res;
    auto it = connectedClusterIndices.begin();
    res = *it;
    // Merge all clusters to first one, starting from second one
    ++it;
    for (; it != end(connectedClusterIndices); ++it)
    {
      auto clusterToMerge = std::move(connectionClusters[*it]);
      connectionClusters.erase(begin(connectionClusters) + *it);
      connectionClusters[res].insert(begin(clusterToMerge), end(clusterToMerge));
    }
    return res;
  };

	// Check for connection with previous items 
	auto findPrevItemsConnectedClusterIndex = [&](int rowInd, int colInd) -> int
	{
		if (!canBeConnected(sourceData[rowInd][colInd]))
			return false;

    // Collect all clusters that current item is connected to
    std::set<int> connectedClusterIndices;
    
		int connectedClusterIndex = -1;
		if (colInd > 0 && clusterFinder(rowInd, colInd - 1, connectedClusterIndex)) connectedClusterIndices.insert(connectedClusterIndex);
		if (rowInd > 0 )
		{
			if (clusterFinder(rowInd - 1, colInd, connectedClusterIndex)) connectedClusterIndices.insert(connectedClusterIndex);
			if (colInd > 0 && clusterFinder(rowInd - 1, colInd-1, connectedClusterIndex)) connectedClusterIndices.insert(connectedClusterIndex);
			if (colInd < column-1 && clusterFinder(rowInd - 1, colInd + 1, connectedClusterIndex)) connectedClusterIndices.insert(connectedClusterIndex);
		}

    // merge clusters, get single cluster index
    connectedClusterIndex = mergeClusters(std::move(connectedClusterIndices));
		return connectedClusterIndex;
	};

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			if (!canBeConnected(sourceData[i][j]))
				continue;

			// Find if current item is connected to any cluster
			int clusterIndex = findPrevItemsConnectedClusterIndex(i, j);
			if (clusterIndex >= 0)
				connectionClusters[clusterIndex].insert({ i, j });
			else // No connection found, create new cluster
				connectionClusters.push_back(ConnectionCluster{ { i, j } });
		}
	}

	auto maxIt = std::max_element(begin(connectionClusters), end(connectionClusters), 
		[](const ConnectionCluster& lhs, const ConnectionCluster& rhs) { return lhs.size() < rhs.size(); });
	
	if (maxIt != end(connectionClusters))
		return maxIt->size();

	return -1;
}


struct Node {
  int data;
  Node* left;
  Node* right;
};

bool isBinaryNode(Node* node) {
  bool leftIsLess = node->left ? node->left->data < node->data : true;
  bool rightIsGreater = node->right ? node->right->data > node->data : true;
  return leftIsLess && rightIsGreater;
}

void addChildren(Node* node, std::queue<Node*>& res)
{
  if (node->left)
  {
    res.push(node->left);
  }

  if (node->right)
  {
    res.push(node->right);
  }
}

bool checkBST(Node* root) {
  if (!root) {
    return false;
  }
  std::queue<Node*> nodesToProcess;
  addChildren(root, nodesToProcess);
  while (nodesToProcess.size()) {
    auto front = nodesToProcess.front();
    if (!isBinaryNode) {
      return false;
    }
    addChildren(front, nodesToProcess);
    nodesToProcess.pop();
  }
  return true;
}