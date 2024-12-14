#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void dfsMatrix(const vector<vector<int>>& matrix, vector<int>& distances, int current, int depth) {
    distances[current] = depth;

    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[current][i] && distances[i] > depth + 1) {
            dfsMatrix(matrix, distances, i, depth + 1);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<vector<int>> matrix = {
        {0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 1, 0}
    };

    int startNode = 0;
    vector<int> distances(matrix.size(), numeric_limits<int>::max());
    dfsMatrix(matrix, distances, startNode, 0);

    cout << "Расстояния от вершины " << startNode << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Вершина " << i << ": " << distances[i] << endl;
    }

    return 0;
}
