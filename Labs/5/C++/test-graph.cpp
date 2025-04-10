#include "graph.h"

int main() {
    //BFS DFS
    {
        GraphWithoutDistance Graph = {
            {1, {2, 3}},
            {2, {1, 3, 4, 5}},
            {3, {1, 2}},
            {4, {2, 5}},
            {5, {2, 4}}
        };

        std::cout << "BFS: " << BFS(Graph, 1) << std::endl;
        std::cout << "DFS: " << DFS(Graph, 1) << std::endl;
    }

    //Dijkstra
    {
        std::cout << "\nDijkstra" << std::endl;
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

        for (const auto& [node, cost] : Costs) {
            std::cout << "Расстояние до " << node << ": ";
            if (cost == INF) {
                std::cout << "нет пути";
            } else {
                std::cout << cost << " (путь: ";
                print_path(Parents, node);
                std::cout << ")";
            }
            std::cout << std::endl;
        }
    }

    //FloydWarshall
   { 
        std::cout << "\nFloydWarshall" << std::endl;
        MatrixType graphWarshall = {
            {0,   8,   4, INF, INF, INF}, 
            {INF, 0,  10, INF,   6, INF}, 
            {INF, INF, 0,   5,  13, INF}, 
            {INF, INF, INF, 0,   3,   3}, 
            {INF, INF, INF, INF, 0,   4}, 
            {INF, INF, INF, INF, INF, 0} 
        };
        FloydWarshall(graphWarshall);
        printMatrix(graphWarshall);
    }

    //Prima
    {
        std::cout << "\nPrima" << std::endl;
        GraphType graph = {
            {0, {{1, 4}, {3, 3}}},
            {1, {{0, 4}, {2, 1}, {3, 2}, {4, 8}}},
            {2, {{1, 1}, {4, 1}}},
            {3, {{0, 3}, {1, 2}, {4, 1}}},
            {4, {{1, 8}, {2, 1}, {3, 1}}}
        };

        GraphType mst = Prima(graph, 0);

        std::cout << "Minimum Spanning Tree:\n";
        for (const auto& [u, neighbors] : mst) {
            for (const auto& [v, weight] : neighbors) {
                std::cout << u << " - " << v << " : " << weight << '\n';
            }
        }
    }

    // Kraskala
    {
        std::cout << "\nKraskala" << std::endl;
        GraphType graph = {
            {1, {{2, 2}, {3, 1}, {4, 3}, {6, 6}}},
            {2, {{1, 2}, {4, 1}, {5, 3}}},
            {3, {{1, 1}, {4, 2}, {6, 3}}},
            {4, {{1, 3}, {2, 1}, {3, 2}, {7, 1}}},
            {5, {{2, 3}, {7, 4}}},
            {6, {{1, 6}, {3, 3}, {7, 7}}},
            {7, {{4, 1}, {5, 4}, {6, 7}}}
        };

        GraphType mst = Kraskala(graph);
        std::cout << "Minimum Spanning Tree:\n";
        for (const auto& [u, neighbors] : mst) {
            for (const auto& [v, weight] : neighbors) {
                std::cout << u << " - " << v << " : " << weight << '\n';
            }
        }
    }
}