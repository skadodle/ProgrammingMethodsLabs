#include "graph.h"

// !DELETE DEBUG
void LogState(std::ofstream& log, int step, PriorityQueueType& pqCopy, CostsType& cost, ParentsType& parent, std::unordered_set<int>& inMST, GraphType& mst) {
    log << "=== Step " << step << " ===\n";
    log << "Priority Queue: [";

    PriorityQueueType pq = pqCopy;
    while (!pq.empty()) {
        auto [w, n] = pq.top(); pq.pop();
        log << "(" << w << ", " << n << ") ";
    }
    log << "]\n";

    log << "minWeight:\n";
    for (const auto& [node, w] : cost)
        log << "  " << node << " = " << (w == INF ? "INF" : std::to_string(w)) << "\n";

    log << "parent:\n";
    for (const auto& [node, p] : parent)
        log << "  " << node << " ← " << p << "\n";

    log << "inMST: { ";
    for (int u : inMST) log << u << " ";
    log << "}\n";

    log << "MST:\n";
    for (const auto& [u, neighbors] : mst)
        for (const auto& [v, w] : neighbors)
            log << "  " << u << " - " << v << " : " << w << "\n";

    log << "\n";
}
// !END DEBUG

void print_path(ParentsType& parents, int node) {
    if (parents.find(node) == parents.end()) {
        std::cout << node;
        return;
    }
    print_path(parents, parents.at(node));
    std::cout << " -> " << node;
}

void printMatrix(MatrixType& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == INF) std::cout << "INF ";
            else std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}