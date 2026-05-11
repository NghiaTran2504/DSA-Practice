#include <iostream>
#include <cstring>

using namespace std;

//DFS with input is adjacency matrix

void readInput (int n, int** a){
    cin.ignore();
    for (int i = 1; i <= n; ++i){
        char *s = new char [n + 5];
        cin.getline (s, 1000);

        char* token = strtok (s, " ");
        while (token != NULL){
            a[i][atoi(token)] = a[atoi(token)][i] = 1;
            token = strtok (NULL, " ");
        }
        delete[] s;
    }
}

void dfs (int u, int ** a, int n, bool visited[]){
    cout << u << " ";
    visited[u] = true;

    for (int j = 1; j <= n; ++j){
        if (a[u][j] == 1 && !visited[j]){
            dfs (j, a, n, visited);
        }
    }
}
int main()
{
    int n; cin >> n;
    int** a = new int*[n+5];
    for (int i = 1; i <= n; ++i){
        a[i] = new int [n+5]{};
    }
    readInput (n, a);

    bool visited[n+5]{};

    dfs (1, a, n, visited);
    return 0;
}