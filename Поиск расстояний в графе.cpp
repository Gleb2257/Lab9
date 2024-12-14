#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateAdjacencyMatrix(vector<vector<int>>& matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0; 
            }
            else {
                int edge = rand() % 2; 
                matrix[i][j] = edge;
                matrix[j][i] = edge; 
            }
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    srand(time(0));

    int n;
    cout << "Введите количество вершин графа: ";
    cin >> n;

    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));
    generateAdjacencyMatrix(adjacencyMatrix, n);

    cout << "Сгенерированная матрица смежности:\n";
    printMatrix(adjacencyMatrix);

    return 0;
}
