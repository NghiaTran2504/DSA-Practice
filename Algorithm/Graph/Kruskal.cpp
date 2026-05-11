#include <iostream>

using namespace std;

struct Edge{
    int vertex;
    int neighbor;
    int weight;

    Edge(){};
    Edge (int u, int v, int w){
        vertex = u;
        neighbor = v;
        weight = w;
    }
    
    void print()
    {
        cout << vertex << " " << neighbor << " " << weight << "\n";
    }
};

const int max_dinh = 1e5;
int n, m;
int parent[max_dinh], sz[max_dinh];
Edge *edge_list;

void nhap (){
    cin >> n >> m;
    edge_list = new Edge [m + 1];
    int idx = 0;
    for (int i = 0; i < m; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        edge_list[idx++] = Edge (u, v, w);
    }
}

void make_set()
{
    for (int i = 1; i <= n; ++i){
        parent[i] = i;
        sz[i] = 1;
    }
}

int find (int v){
    if (v == parent[v])
        return v;
    return parent[v] = find (parent[v]);
}

bool Union (int a, int b){
    a = find (a);
    b = find (b);
    if (a == b) return false;
    else{
        if (sz[a] < sz[b]) swap (a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
    return true;
}

bool maxHeap (Edge a, Edge b) {return a.weight > b.weight;};

void heapify(int u, int Size, bool (*cmp) (Edge, Edge)){
    int node = u;
    while (1){
        int left = 2 * node + 1;
        int right = 2 * node + 2;
        int largest = node;

        if (left < Size && cmp (edge_list[left], edge_list[largest]))
            largest = left;
        if (right < Size && cmp (edge_list[right], edge_list[largest]))
            largest = right;

        if (largest == node) return;
        swap (edge_list[largest], edge_list[node]);
        node = largest;
    }
}

void heapsort()
{
    for (int i = m / 2 - 1; i >= 0; --i){
        heapify (i, m, maxHeap);
    }

    for (int i = m - 1; i >= 0; --i){
        swap (edge_list[0], edge_list[i]);
        heapify (0, i, maxHeap);
    }
}
void kruskal ()
{
    // B1: Tạo cây khung cực tiểu rỗng
    int d_mst = 0;
    int sum_mst = 0;
    Edge mst [n+5];
    int idx = 0;
    // B2: Sắp xếp các cạnh
    heapsort();

    // B3: Iteration 
    for (int i = 0; i < m; ++i){
        if (d_mst == n - 1) break;
        Edge e = edge_list[i];
        if (Union (e.vertex, e.neighbor)){
            e.print();
            mst[idx++] = e;
            d_mst ++;
            sum_mst += e.weight;
        }
    }

    //Tra ve kq
    cout << "Do dai cay khung nho nhat: " << sum_mst << "\n";
    cout << "Cay khung nho nhat (Kruskal): ";
    bool visited[n + 1]{};
    for (int i = 0; i < idx; ++i){
        if (!visited[mst[i].vertex]){
            visited[mst[i].vertex] = true;
            visited[mst[i].neighbor] = true;
            cout << mst[i].vertex << " " << mst[i].neighbor << " ";
        }
        else{
            visited[mst[i].neighbor] = true;
            cout << mst[i].neighbor << " ";
        }
    }
}
int main()

{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    nhap();
    make_set();
    kruskal();
    delete[] edge_list;
    return 0;
}