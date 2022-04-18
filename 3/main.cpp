//https://contest.yandex.ru/contest/36361/run-report/67501361/


#include <iostream>
#include <vector>
#include <algorithm>


void ReverseDFS(const std::vector<std::vector<int>>& t_graph,
                int vertex, std::vector<int>& leaves, std::vector<bool>& visited) {
    static int time = 0;
    visited[vertex] = true;
    for (int u : t_graph[vertex]) {
        if (!visited[u]) {
            ReverseDFS(t_graph, u, leaves, visited);
        }
    }
    leaves[vertex] = ++time;
}


void DFS(const std::vector<std::vector<int>>& graph, int v, std::vector<bool>& visited,
         std::vector<int>& components, int component) {
    visited[v] = true;
    components[v] = component;
    for (int u : graph[v]) {
        if (!visited[u]) {
            DFS(graph, u, visited, components, component);
        }
    }
}


std::vector<int> MainDFS(const std::vector<std::vector<int>>& graph, const std::vector<int>& leaves,
                         int n, const std::vector<std::vector<int>>& t_graph) {
    std::vector<std::pair<int, int>> leaves_and_vertices;
    leaves_and_vertices.reserve(leaves.size());
    for (int i = 0; i < leaves.size(); ++i) leaves_and_vertices.emplace_back(leaves[i], i);
    std::sort(leaves_and_vertices.rbegin(), leaves_and_vertices.rend());

    std::vector<int> components(n);
    std::vector<bool> visited(n, false);

    int component = 0;
    for (auto& [leave, v] : leaves_and_vertices) {
        if (!visited[v]) {
            DFS(graph, v, visited, components, component);
            ++component;
        }
    }
    components.push_back(component);
    return components;
}


std::vector<int> Kosaraju(const std::vector<std::vector<int>>& graph,
                          const std::vector<std::vector<int>>& t_graph, int n) {
    std::vector<int> leaves(n);
    std::vector<bool> visited(n, false);
    for (int v = 0; v < n; ++v) {
        if (!visited[v]) {
            ReverseDFS(t_graph, v, leaves, visited);
        }
    }

    std::vector<int> components = MainDFS(graph, leaves, n, t_graph);
    return components;
}


std::vector<std::vector<int>> MakeGraphCondensation(const std::vector<int>& components,
                                       const std::vector<std::vector<int>>& graph, int n, int count) {
    std::vector<std::vector<int>> condensation(count);
    for (int i = 0; i < n; ++i) {
        std::vector<bool> flag(count, false);
        for (auto v : graph[i]) {
            if (components[i] != components[v] && !flag[components[v]]) {  // не добавлять повторяющиеся элементы
                condensation[components[i]].push_back(components[v]);
                flag[components[v]] = true;
            }
        }
    }
    return condensation;
}


int ComplementToStronglyConnected(const std::vector<std::vector<int>>& graph,
                                  const std::vector<std::vector<int>>& t_graph, int n) {
    std::vector<int> components = Kosaraju(graph, t_graph, n);
    int count = components[n];
    components.pop_back();
    std::vector<std::vector<int>> condensation = MakeGraphCondensation(components, graph, n, count);
    std::vector<std::vector<int>> condensation_t = MakeGraphCondensation(components, t_graph, n, count);

    int origins = 0, drains = 0;
    if (count == 1) {
        return 0;
    }

    for (int i = 0; i < count; ++i) {
        if (condensation[i].empty()) {
            ++origins;
        }
    }

    for (int i = 0; i < count; ++i) {
        if (condensation_t[i].empty()) {
            ++drains;
        }
    }

    return std::max(drains, origins);
}


int main() {
    int v, e;
    std::cin >> v;
    std::cin >> e;
    std::vector<std::vector<int>> graph(v);
    std::vector<std::vector<int>> t_graph(v);
    for (int i = 0; i < e; ++i) {
        int p1, p2;
        std::cin >> p1 >> p2;
        graph[p1 - 1].push_back(p2 - 1);
        t_graph[p2 - 1].push_back(p1 - 1);
    }
    std::cout << ComplementToStronglyConnected(graph, t_graph, v) << std::endl;
    return 0;
}
