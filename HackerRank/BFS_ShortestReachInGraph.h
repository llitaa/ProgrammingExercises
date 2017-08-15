#pragma once
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <list>


// https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach

using namespace std;


class Graph {
public:
	Graph(int n) {
		_nodes = vector<vector<int>>(n);
	}

	void add_edge(int u, int v) {
		_nodes[u].push_back(v);
		_nodes[v].push_back(u);
	}

	vector<int> shortest_reach(int start) {
		vector<int> distances(_nodes.size(), -1);
		queue<int> nodesToProcess;
		unordered_set<int> visitedNodes;
		distances[start] = 0;
		nodesToProcess.push(start);
		while (!nodesToProcess.empty()) {
			auto currentNode = nodesToProcess.front();
			nodesToProcess.pop();
			auto& adjacentNodes = _nodes[currentNode];
			for (auto& adjNode : adjacentNodes) {
				if (visitedNodes.find(adjNode) == end(visitedNodes)) {
					nodesToProcess.push(adjNode);
					visitedNodes.emplace(adjNode);
					const int EDGE_LENGTH = 6;
					distances[adjNode] = distances[currentNode] + EDGE_LENGTH;
				}
			}
		}
		return distances;
	}

private:
	vector<vector<int>> _nodes;
};

int runBFS() {
	int queries;
	cin >> queries;

	for (int t = 0; t < queries; t++) {
		int n, m;
		cin >> n;
		// Create a graph of size n where each edge weight is 6: 
		Graph graph(n);
		cin >> m;
		// read and set edges
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--, v--;
			// add each edge to the graph
			graph.add_edge(u, v);
		}
		int startId;
		cin >> startId;
		startId--;
		// Find shortest reach from node s
		vector<int> distances = graph.shortest_reach(startId);

		for (unsigned i = 0; i < distances.size(); i++) {
			if (i != startId) {
				cout << distances[i] << " ";
			}
		}
		cout << endl;
	}

	return 0;
}
