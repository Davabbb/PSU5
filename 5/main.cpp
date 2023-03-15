//https://contest.yandex.ru/contest/36361/run-report/67471273/

#include <iostream>
#include <vector>
#include <queue>

struct Comparator {
    bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
        return a.second < b.second;
    }
};

std::vector<int> next_vertex(int top, const std::vector<std::vector<double>>& grath, int n) {
    std::vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (grath[top][i] != -1)
            res.push_back(i);
    }
    return res;
}

bool arbitration(const std::vector<std::vector<double>>& grath, int n) {
    for (int i = 0; i < n; ++i) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Comparator> data;
        std::vector<double> trade(n, 1);
        data.push(std::pair<int, int> (i, 1));
        while (!data.empty()) {
            auto top = data.top();
            data.pop();
            if (i == top.first && trade[i] > 1) return true;
            std::vector<int> next = next_vertex(top.first, grath, n);
            for (int vertex : next) {
                double new_trade = trade[top.first] * grath[top.first][vertex];
                if (new_trade > trade[vertex]) {
                    trade[vertex] = new_trade;
                    data.push(std::pair<int, int> (vertex, trade[vertex]));
                }
            }
        }
    }
    return false;
}


int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<double>> data(n, std::vector<double>(n, 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double num;
            if (i != j) {
                std::cin >> num;
                data[i][j] = num;
            }
         }
    }

    if (arbitration(data, n)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
