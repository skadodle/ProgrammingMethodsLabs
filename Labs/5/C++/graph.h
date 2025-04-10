#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>

#define GraphWithoutDistance std::unordered_map<int, std::vector<int>>
#define GraphType std::unordered_map<int, std::unordered_map<int, int>>  // GRAPH[from][to] = weight
#define CostsType std::unordered_map<int, int>                           // COSTS[node] = distance
#define ParentsType std::unordered_map<int, int>                         // PARENTS[node] = parent
#define MatrixType std::vector<std::vector<int>> 
#define PriorityQueueType std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>  // distance, vershina
#define INF std::numeric_limits<int>::max()

//funcs.cpp
// !DELETE DEBUG
void LogState(std::ofstream&, int, PriorityQueueType&, CostsType&, ParentsType&, std::unordered_set<int>&, GraphType&);
// !END DEBUG
void print_path(ParentsType&, int);
void printMatrix(MatrixType&);

//graph.cpp
int BFS(GraphWithoutDistance, int);
int DFS(GraphWithoutDistance, int);
void Dijkstra(const GraphType&, int, CostsType&, ParentsType&);

GraphType Kraskala(GraphType&);
GraphType Prima(GraphType&, int);
void FloydWarshall(MatrixType&);