#include <iostream>

using namespace std;
using ll = long long;

struct edge{
    int vertex, neighbor, weight;

    edge(){vertex = 0; neighbor = 0, weight = 0;}
    edge (int u, int v, int w){
        vertex = u;
        neighbor = v;
        weight = w;
    }

    void print(){
        cout << vertex << " "  << neighbor << " " << weight << "\n";
    }
};

const int nmax = 1e4 + 5;
const int INF = 1e6 + 5;
int n, m;
int q[1005];
edge edgeList [nmax];
int cost[1005];

void nhap(){
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> q[i];
    }
    cin >> m;
    for (int i = 0; i < m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        edgeList[i] = edge (a, b, c);
    }
}


void solve(){
    nhap();
    for (int i = 1; i <= n; ++i){
        cost[i] = INF;
    }

    for (int i = 0; i < m; ++i){
        int trongso = edgeList[i].weight;
        int vertex = edgeList[i].vertex;
        int neighbor = edgeList[i].neighbor;

        if (cost[neighbor] > trongso)
            cost[neighbor] = trongso;
    }

    ll sumCost = 0;
    int dem = 0;
    for (int i = 1; i <= n; ++i){
        if (cost[i] >= INF){
            dem++;
        }
        else sumCost += cost[i];
    }
    if (dem > 1) cout << -1;
    else cout << sumCost;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}