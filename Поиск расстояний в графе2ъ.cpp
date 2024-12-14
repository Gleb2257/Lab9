#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;


vector<vector<int>> generateGraph(int n) {
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));
    srand(time(0)); 

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int edge = rand() % 2; // 
            adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = edge;
        }
    }

    return adjacencyMatrix;
}

// Алгоритм поиска расстояний
void findDistances(const vector<vector<int>>& adjacencyMatrix, int start) {
    int n = adjacencyMatrix.size();
    vector<int> distances(n, INT_MAX); 
    queue<int> q;

    distances[start] = 0; 
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (adjacencyMatrix[current][i] == 1 && distances[i] == INT_MAX) {
                distances[i] = distances[current] + 1;
                q.push(i);
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

    int n;
    cout << "Введите количество вершин графа: ";
    cin >> n;

    vector<vector<int>> adjacencyMatrix = generateGraph(n);

    // Вывод сгенерированной матрицы смежности
    cout << "Сгенерированная матрица смежности (" << n << "x" << n << "):\n";
    for (const auto& row : adjacencyMatrix) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    int start;
    cout << "Введите начальную вершину (1-" << n << "): ";
    cin >> start;
    start--;

    
    findDistances(adjacencyMatrix, start);

    return 0;
}
