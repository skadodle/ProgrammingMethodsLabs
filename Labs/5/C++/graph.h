#pragma once

#include <iostream>
#include <limits>

#include <unordered_map>
#include <vector>
#include <set>
#include <stack>
#include <queue>

#define GraphWithoutDistance std::unordered_map<int, std::vector<int>>
#define GraphType std::unordered_map<int, std::unordered_map<int, int>>  // GRAPH[from][to] = weight
#define CostsType std::unordered_map<int, int>                           // COSTS[node] = distance
#define ParentsType std::unordered_map<int, int>                         // PARENTS[node] = parent
#define MatrixType std::vector<std::vector<int>> 

int BFS(GraphWithoutDistance, int);
int DFS(GraphWithoutDistance, int);
void Dijkstra(const GraphType&, int, CostsType&, ParentsType&);

GraphType Kryskala();
GraphType Prima();
MatrixType Floyd_Yorshell();