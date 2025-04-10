#include "graph.h"

int BFS(GraphWithoutDistance G, int v) {
    if (G.empty())
        return 0;

    std::unordered_set<int> visited;
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

    std::unordered_set<int> visited;
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
    PriorityQueueType pq;
    
    for (const auto& [node, el] : G) {
        costs[node] = INF;
    }
    costs[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int current_node = pq.top().second;
        int current_cost = pq.top().first;
        pq.pop();

        if (current_cost > costs[current_node]) continue;

        for (const auto& [neighbor, weight] : G.at(current_node)) {
            int new_cost = current_cost + weight;

            if (new_cost < costs[neighbor]) {
                costs[neighbor] = new_cost;
                parents[neighbor] = current_node;
                pq.push({new_cost, neighbor});
            }
        }
    }
}

GraphType Kraskala(GraphType& graph) {
    if (graph.empty()) return {};

    std::vector<std::tuple<int, int, int>> edges; // (weight, u, v)
    std::unordered_map<int, int> parent;
    GraphType mst;

    for (const auto& [u, neighbors] : graph) {
        parent[u] = u;
        for (const auto& [v, weight] : neighbors) {
            edges.emplace_back(weight, u, v);
        }
    }

    std::sort(edges.begin(), edges.end());

    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };

    for (const auto& edge : edges) {
        int weight = std::get<0>(edge);
        int u = std::get<1>(edge);
        int v = std::get<2>(edge);

        int u_root = find(u);
        int v_root = find(v);

        if (u_root != v_root) {
            mst[u][v] = weight;
            parent[v_root] = u_root;
        }
    }

    return mst;
}

GraphType Prima(GraphType& graph, int start) {
    if (graph.empty()) return {};

    GraphType mst;
    CostsType minWeight;
    ParentsType parent;
    std::unordered_set<int> inMST;
    
    for (const auto& [node, el] : graph) {
        minWeight[node] = INF;
    }
    minWeight[start] = 0;

    PriorityQueueType pq;
    pq.push({0, start});

    // !DELETE DEBUG
    std::ofstream log("log.txt");
    int step = 0;
    // !END DEBUG

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST.count(u)) {
            // !DELETE DEBUG
            LogState(log, step++, pq, minWeight, parent, inMST, mst);
            // !END DEBUG
            continue;
        }
        inMST.insert(u);

        // Добавляем ребро в MST (кроме стартовой вершины)
        if (parent.find(u) != parent.end()) {
            mst[parent[u]][u] = minWeight[u];
        }

        // Обновляем ключи соседей
        for (const auto& [v, weight] : graph.at(u)) {
            if (!inMST.count(v) && weight < minWeight[v]) {
                minWeight[v] = weight;
                parent[v] = u;
                pq.push({minWeight[v], v});
            }
        }

        // !DELETE DEBUG
        LogState(log, step++, pq, minWeight, parent, inMST, mst);
        // !END DEBUG
    }

    // !DELETE DEBUG
    log.close();
    // !END DEBUG

    return mst;
}

void FloydWarshall(MatrixType& dist) {
    int n = dist.size();
    
    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;
    
    // Основная часть алгоритма
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}