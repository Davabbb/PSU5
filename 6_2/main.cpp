//https://contest.yandex.ru/contest/36361/run-report/66591049/

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

int get_dsu(int p, std::vector<int>& parent) {
    if (p != parent[p])
        parent[p] = get_dsu(parent[p], parent);
    return parent[p];
}

void dsu(int p1, int p2, std::vector<int>& parent, std::vector<int>& size) {
    p1 = get_dsu(p1, parent);
    p2 = get_dsu(p2, parent);
    if (size[p1] < size[p2]) {
        std::swap(p1, p2);
    }
    parent[p2] = p1;
    size[p1] += size[p2];
}

int kraskal(std::vector<Ribs> data, int count_node, int count_ribs) {
    int answer = 0;
    std::vector<int> parent(count_node), size(count_node);
    for (int i = 0; i < count_node; i++) {
        parent[i] = i;
        size[i] = i;
    }
    sort(data);
    for (int i = 0; i < count_ribs; i++) {
        int p1 = data[i].point1, p2 = data[i].point2, w = data[i].weight;
        if (get_dsu(p1, parent) != get_dsu(p2, parent)) {
            answer += w;
            dsu(p1, p2, parent, size);
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
