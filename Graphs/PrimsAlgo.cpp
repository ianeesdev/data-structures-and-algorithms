#include<iostream>
#include<climits>
using namespace std;

void prims(int **graph, int n) {
    int distance[n];
    int parent[n];
    bool visited[n];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        parent[i] = INT_MAX;
        visited[i] = false;
    }
    distance[0] = 0;
    for (int p = 0; p < n; p++) {
        int min = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (min == -1 || distance[j] < distance[min])) {
                min = j;
            }
        }
        visited[min] = true;
        for (int k = 0; k < n; k++) {
            if (graph[min][k] != 0 && (graph[min][k]) < distance[k]) {
                if (!visited[k]) {
                    distance[k] = graph[min][k];
                    parent[k] = min;
                }
            }
        }
    }
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << " \t" << distance[i] << endl;
    }
}

int main() {
    int rows, col;
    cout << "\n\t\tP R I M S\n";
    cout << "\nEnter number of vertices: ";
    cin >> rows;
    col = rows;
    int **graph = new int*[rows];
    for (int i = 0; i < rows; i++) {
        graph[i] = new int[col];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col; j++) {
            cout << "Enter distance: ";
            cin >> graph[i][j];
        }
    }
    // int graph[8][8] = {
    //     {0,0,3,0,25,18,2,0},
    //     {0,0,0,2,7,0,0,3},
    //     {0,4,0,3,0,3,0,0},
    //     {10,7,3,18,0,0,0,0},
    //     {0,10,0,25,0,0,7,0},
    //     {4,9,0,0,0,0,3,0},
    //     {0,8,0,0,0,10,0,4},
    //     {8,0,4,0,10,7,0,9}
    // };
    // int graph[6][6] = {
    //     {0,16,0,0,19,21},
    //     {16,0,6,5,0,11},
    //     {0,6,0,10,0,0},
    //     {0,5,10,0,18,14},
    //     {19,0,0,18,0,33},
    //     {21,11,0,14,33,0}
    // };
    prims(graph, rows);
}