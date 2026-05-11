#include <iostream>

using namespace std;

const int nmax = 2e5 + 5;
bool visited[nmax];

int main() 
{
    int n; cin >> n;
    for (int i = 0; i < n - 1; ++i){
        int x;
        cin >> x;
        visited[x] = true;
    }
    for (int i = 1; i <= 200001; ++i){
        if (!visited[i]){
            cout << i;
            break;
        }
    }
    return 0;
}