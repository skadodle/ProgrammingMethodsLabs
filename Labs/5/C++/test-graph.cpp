#include "graph.h"

void print_path(const ParentsType&, int);

int main() {
    GraphWithoutDistance Graph = {
        {1, {2, 3}},
        {2, {1, 3, 4, 5}},
        {3, {1, 2}},
        {4, {2, 5}},
        {5, {2, 4}}
    };

    std::cout << "BFS: " << BFS(Graph, 1) << std::endl;
    std::cout << "DFS: " << DFS(Graph, 1) << std::endl;

    GraphType Graph1 = {
        {0, {{1, 8}, {2, 4}}},
        {1, {{2, 10}, {4, 6}}},
        {2, {{3, 5}, {4, 13}}},
        {3, {{4, 3}, {5, 3}}},
        {4, {{5, 4}}},
        {5, {}}
    };

    CostsType Costs;
    ParentsType Parents;

    Dijkstra(Graph1, 0, Costs, Parents);

    // Выводим результаты
    for (const auto& [node, cost] : Costs) {
        std::cout << "Расстояние до " << node << ": ";
        if (cost == std::numeric_limits<int>::max()) {
            std::cout << "нет пути";
        } else {
            std::cout << cost << " (путь: ";
            print_path(Parents, node);
            std::cout << ")";
        }
        std::cout << std::endl;
    }
}

void print_path(const ParentsType& parents, int node) {
    if (parents.find(node) == parents.end()) {
        std::cout << node;
        return;
    }
    print_path(parents, parents.at(node));
    std::cout << " -> " << node;
}