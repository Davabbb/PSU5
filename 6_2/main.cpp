//https://contest.yandex.ru/contest/36361/run-report/68016758/

#include <iostream>
#include <vector>
#include <algorithm>

struct Ribs{
    int weight{};
    int point1{};
    int point2{};
};

void sort(std::vector<Ribs>& data) {
    std::sort(data.begin(), data.end(), [&data](Ribs elem1, Ribs elem2) {
        return elem1.weight < elem2.weight;
    });
}


int find(const std::vector<int>& parent, int p) {
    if (p == parent[p]) {
        return p;
    }
    return find(parent, parent[p]);
}


void union_set(std::vector<int>& parent, std::vector<int>& rank, int p1, int p2) {
    p1 = find(parent, p1);
    p2 = find(parent, p2);
    if (rank[p1] > rank[p2]) {
        std::swap(p1, p2);
    }
    rank[p2] = std::max(rank[p2], rank[p1] + 1);
    parent[p1] = parent[p2];
}


int kraskal(std::vector<Ribs> data, int count_node, int count_ribs) {
    int answer = 0;
    std::vector<int> parent(count_node), rank(count_ribs);
    for (int i = 0; i < count_node; i++) {
        parent[i] = i;
    }
    sort(data);
    for (int i = 0; i < count_ribs; ++i) {
        int p1 = data[i].point1, p2 = data[i].point2, w = data[i].weight;
        if (find(parent, p1) != find(parent, p2)) {
            union_set(parent, rank, p1, p2);
            answer += w;
        }
    }
    return answer;
}

int main() {
    int count_node, count_ribs;
    std::cin >> count_node >> count_ribs;

    std::vector<Ribs> data(count_ribs);

    for (int i = 0; i < count_ribs; i++) {
        Ribs rib{};
        int point1, point2, weight;
        std::cin >> point1 >> point2 >> weight;
        rib.point1 = point1 - 1;
        rib.point2 = point2 - 1;
        rib.weight = weight;
        data[i] = rib;
    }
    std::cout << kraskal(data, count_node, count_ribs);

    return 0;
}
