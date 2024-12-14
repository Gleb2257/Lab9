#include <iostream>
#include <vector>
#include <queue>
#include <limits> 

using namespace std;

// Алгоритм поиска расстояний
void findDistances(const vector<vector<int>>& adjacencyList, int start) {
    int n = adjacencyList.size();
    vector<int> distances(n, INT_MAX); 
    queue<int> q;

    distances[start] = 0; 
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adjacencyList[current]) {
            if (distances[neighbor] == INT_MAX) {
                distances[neighbor] = distances[current] + 1;
                q.push(neighbor);
            }
        }
    }

    // Вывод результатов
    cout << "Расстояния от вершины " << start + 1 << ":\n";
    for (int i = 0; i < n; i++) {
        if (distances[i] == INT_MAX) {
            cout << "Вершина " << i + 1 << ": недостижима\n";
        }
        else {
            cout << "Вершина " << i + 1 << ": " << distances[i] << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n, m;
    cout << "Введите количество вершин и рёбер графа: ";
    cin >> n >> m;

    if (cin.fail() || n <= 0 || m < 0) {
        cout << "Ошибка: количество вершин должно быть больше 0, а количество рёбер неотрицательным." << endl;
        return 1;
    }

    // Список смежности
    vector<vector<int>> adjacencyList(n);

    cout << "Введите рёбра графа (по два числа через пробел, от 1 до " << n << "):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (cin.fail() || u < 1 || u > n || v < 1 || v > n) {
            cout << "Ошибка: вершины рёбер должны быть в диапазоне от 1 до " << n << "." << endl;
            return 1;
        }

        u--; v--; 
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); 
    }

    int start;
    cout << "Введите начальную вершину (1-" << n << "): ";
    cin >> start;

   
    if (cin.fail() || start < 1 || start > n) {
        cout << "Ошибка: начальная вершина должна быть в диапазоне от 1 до " << n << "." << endl;
        return 1;
    }
    start--; 

    findDistances(adjacencyList, start);

    return 0;
}
