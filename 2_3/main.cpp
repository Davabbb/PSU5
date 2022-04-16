//https://contest.yandex.ru/contest/36361/run-report/67433407/


#include <iostream>
#include <vector>
#include <queue>

int invert(int color) {
    return color == 1 ? 2 : 1;
}

bool dfs(int vertex, const std::vector<std::vector<int>>& grath, std::vector<int>& colors, int color) {
    colors[vertex] = color;

    for (int v : grath[vertex]) {
        if (colors[v] == 0) {
            if (not dfs(v, grath, colors, invert(color))) {
                return false;
            }
        } else if (colors[v] == color) {
            return false;
        }
    }
    return true;
}


int main() {
    int count_node, count_ribs;
    std::cin >> count_node;
    std::cin >> count_ribs;

    std::vector<std::vector<int>> grath(count_node);
    for (int i = 0; i < count_ribs; ++i) {
        int p1, p2;
        std::cin >> p1 >> p2;
        grath[p1].push_back(p2);
        grath[p2].push_back(p1);
    }

    std::vector<int> colors(count_node, 0);
    bool flag = true;
    for (int i = 0; i < count_node; ++i) {
        if (colors[i] == 0) {
            if (not dfs(i, grath, colors, 1)) {
                flag = false;
                break;
            }
        }
    }

    if (flag) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
