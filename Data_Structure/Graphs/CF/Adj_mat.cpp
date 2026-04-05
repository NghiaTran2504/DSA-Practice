#include <iostream>

using namespace std;

// BIEU DIEN DO THI BANG MA TRAN KE
int main()
{
    int n, m; cin >> n >> m;
    int adj_mat[n+5][n+5]{};
    for (int i = 0; i < m; ++i){
        int x, y; cin >> x >> y;
        adj_mat[x][y] = adj_mat[y][x] = 1;
    }

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j) 
            cout << adj_mat[i][j] << " ";
        
        cout << "\n";
    }

    return 0;
}