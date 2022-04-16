//https://contest.yandex.ru/contest/36361/run-report/67448799/

#include <iostream>
#include <vector>
#include <set>

struct Edge {
    int Vertex = 0;
    int Weight = 0;
};


int dijkstra(const std::vector<std::vector<Edge>>& graph, int start, int end, int n) {
    auto distance = std::vector(graph.size(), std::numeric_limits<int>::max());
    std::set<std::pair<int, int>> q;

    q.insert({0, start});
    distance[start] = 0;
    while (!q.empty()) {
        auto it = q.begin();
        int u = it->second;
        q.erase(it);
        for (auto e : graph[u]) {
            int v = e.Vertex;
            if (distance[u] + e.Weight < distance[v]) {
                auto itv = q.find({distance[v], v});
                if (itv != q.end()) {
                    q.erase(itv);
                }
                distance[v] = distance[u] + e.Weight;
                q.insert({distance[v], v});
            }
        }
    }
    return distance[end];
}


int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;

    std::vector<std::vector<Edge>> grath(n);
    for (int i = 0; i < m; ++i) {
        int p1, p2, len;
        std::cin >> p1 >> p2 >> len;
        grath[p1].push_back({p2, len});
        grath[p2].push_back({p1, len});
    }
    int start, end;
    std::cin >> start >> end;

    std::cout << dijkstra(grath, start, end, n) << std::endl;
    return 0;
}
