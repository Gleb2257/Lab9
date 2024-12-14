#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstdlib>
#include <chrono> 

using namespace std;
using namespace chrono;

vector<vector<int>> generateRandomGraph(int n, int m) {
    vector<vector<int>> adjacencyList(n);
    set<pair<int, int>> edges;
    srand(time(nullptr));

    while (edges.size() < m) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && edges.find({ u, v }) == edges.end() && edges.find({ v, u }) == edges.end()) {
            adjacencyList[u].push_back(v);
            adjacencyList[v].push_back(u);
            edges.insert({ u, v });
        }
    }

    return adjacencyList;
}

void findDistancesBFS(const vector<vector<int>>& adjacencyList, int start, vector<int>& distances) {
    int n = adjacencyList.size();
    distances.assign(n, INT_MAX);
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
}

void dfs(int current, int depth, const vector<vector<int>>& adjacencyList, vector<int>& distances) {
    distances[current] = depth;

    for (int neighbor : adjacencyList[current]) {
        if (distances[neighbor] > depth + 1) {
            dfs(neighbor, depth + 1, adjacencyList, distances);
        }
    }
}

void findDistancesDFS(const vector<vector<int>>& adjacencyList, int start, vector<int>& distances) {
    int n = adjacencyList.size();
    distances.assign(n, INT_MAX);
    dfs(start, 0, adjacencyList, distances);
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n, m;
    cout << "Введите количество вершин и рёбер графа: ";
    cin >> n >> m;

    if (n <= 0 || m < 0) {
        cout << "Ошибка: количество вершин должно быть больше 0, а рёбер неотрицательным." << endl;
        return 1;
    }

    vector<vector<int>> adjacencyList = generateRandomGraph(n, m);

    cout << "Сгенерированный граф (список смежности):\n";
    for (int i = 0; i < adjacencyList.size(); i++) {
        cout << i << ": ";
        for (int neighbor : adjacencyList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    int start = 0;
    vector<int> distances;

    // Измерение времени для BFS
    auto startTimeBFS = high_resolution_clock::now();
    findDistancesBFS(adjacencyList, start, distances);
    auto endTimeBFS = high_resolution_clock::now();
    auto durationBFS = duration_cast<microseconds>(endTimeBFS - startTimeBFS).count();

    // Вывод результатов 
    cout << "\nРезультаты BFS (расстояния от вершины " << start << "):\n";
    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] == INT_MAX) {
            cout << i << ": недостижима\n";
        }
        else {
            cout << i << ": " << distances[i] << "\n";
        }
    }

    // Измерение времени для DFS
    auto startTimeDFS = high_resolution_clock::now();
    findDistancesDFS(adjacencyList, start, distances);
    auto endTimeDFS = high_resolution_clock::now();
    auto durationDFS = duration_cast<microseconds>(endTimeDFS - startTimeDFS).count();

    // Вывод результатов 
    cout << "\nРезультаты DFS (расстояния от вершины " << start << "):\n";
    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] == INT_MAX) {
            cout << i << ": недостижима\n";
        }
        else {
            cout << i << ": " << distances[i] << "\n";
        }
    }

    // Вывод времени 
    cout << "\nВремя выполнения BFS: " << durationBFS << " мкс" << endl;
    cout << "Время выполнения DFS: " << durationDFS << " мкс" << endl;

    return 0;
}

