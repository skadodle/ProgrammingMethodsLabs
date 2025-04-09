#include "graph.h"

int BFS(GraphWithoutDistance G, int v) {
    if (G.empty())
        return 0;

    std::set<int> visited;
    std::queue<int> queue;
    int result = 0;

    queue.push(v);

    while(!queue.empty()) {
        int current = queue.front();
        queue.pop();
        result++;

        for (int neighbor : G[current]) {
            if (!visited.count(neighbor)) {
                queue.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }

    return result;
}

int DFS(GraphWithoutDistance G, int v) {
    if (G.empty())
        return 0;

    std::set<int> visited;
    std::stack<int> stack;
    int result = 0;

    stack.push(v);

    while(!stack.empty()) {
        int current = stack.top();
        stack.pop();
        result++;

        for (int neighbor : G[current]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                stack.push(neighbor);
            }
        }
    }

    return result;
}

void Dijkstra(const GraphType& G, int src, CostsType& costs, ParentsType& parents) {
    // Приоритетная очередь: пары (расстояние, вершина)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    
    // Инициализация
    for (const auto& [node, _] : G) {
        costs[node] = std::numeric_limits<int>::max();
    }
    costs[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int current_node = pq.top().second;
        int current_cost = pq.top().first;
        pq.pop();

        // Если нашли более длинный путь - пропускаем
        if (current_cost > costs[current_node]) continue;

        // Проверяем всех соседей
        for (const auto& [neighbor, weight] : G.at(current_node)) {
            int new_cost = current_cost + weight;

            // Если нашли более короткий путь
            if (new_cost < costs[neighbor]) {
                costs[neighbor] = new_cost;
                parents[neighbor] = current_node;
                pq.push({new_cost, neighbor});
            }
        }
    }
}


GraphType Kryskala() {
    abort();
}

GraphType Prima() {
    abort();
}

MatrixType Floyd_Yorshell() {
    abort();
}