#include <iostream>

using namespace std;

using ll = long long;
struct Pair{
    int vertex;
    ll weight;

    Pair() {vertex = 0; weight = 0;}
    Pair (int v, int w) {vertex = v; weight = w;}
};

struct Node{
    Pair data;
    Node* next;

    Node() {data = Pair(); next = NULL;}
    Node(int v, int w){
        data = Pair (v, w);
        next = NULL;
    }
};

struct Graph{
    Node** adj_list;
    Node** tail;
    int n;

    Graph (int num){
        n = num;
        adj_list = new Node* [n + 5]{};
        tail = new Node* [n+5]{};
    }

    void addNode (int u, int v, int w){
        Node* newNode = new Node (v, w);
        if (adj_list[u] == NULL){
            adj_list[u] = tail[u] = newNode;
        }
        else{
            tail[u] -> next = newNode;
            tail[u] = newNode;
        }
    }

    ~Graph(){
        for (int i = 1; i <= n; ++i){
            Node* curr = adj_list[i];
            while (curr != NULL){
                Node* tmp =curr;
                curr = curr -> next;
                delete tmp;
            }
        }
        delete[] adj_list;
        delete[] tail;
    }
};

bool minHeap (Pair& a, Pair& b) {return a.weight < b.weight;}
struct Priority_queue{
    Pair* heap;
    int size, capacity;
    bool (*cmp) (Pair&, Pair&);

    Priority_queue (int cap, bool (*func) (Pair&, Pair&)){
        capacity = cap;
        size = 0;
        heap = new Pair [cap + 5];
        cmp = func;
    }

    void push (int v, int w){
        heap[size++] = Pair (v, w);
        heapifyUp (size - 1);
    }

    void heapifyUp (int i){
        int node = i;
        while (node > 0){
            int parent = (node - 1) / 2;
            if (cmp (heap[node], heap[parent])){
                swap (heap[node], heap[parent]);
                node = parent;
            }

            else break;
        }
    }

    bool empty(){
        return size == 0;
    }

    Pair pop(){
        if (empty()) return Pair();

        Pair tmp = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown ();
        return tmp;
    }

    void heapifyDown (){
        int node = 0;
        while (1){
            int left = 2 * node + 1;
            int right = 2 * node + 2;
            int smallest = node;

            if (left < size && cmp (heap[left], heap[smallest]))
                smallest = left;
            if (right < size && cmp (heap[right], heap[smallest]))
                smallest = right;

            if (smallest == node) return;
            swap (heap[smallest], heap[node]);
            node = smallest;
        }
    }
};
// ########################################## //

const int max_dinh = 2e5;
int n, m, s;
bool used[max_dinh];
Graph *g;

void nhap(){
    cin >> n >> m >> s;
    g = new Graph (n);

    for (int i = 0; i < m; ++i){
        int u, v, w; cin >> u >> v >> w;
        g -> addNode (u, v, w);
        g -> addNode (v, u, w);
    }
}

void Prim()
{
    Priority_queue pq (m + 5, minHeap);
    pq.push (s, 0);
    ll sum_mst = 0;
    int d_mst = 0;

    while (!pq.empty()){
        Pair top = pq.pop();
        int dinh = top.vertex;
        int trongso = top.weight;

        if (!used[dinh]){
            used[dinh] = true;
            sum_mst += trongso;
            d_mst += 1;

            Node* curr = g -> adj_list[dinh];
            while (curr != NULL){
                if (!used[curr -> data.vertex]){
                    pq.push (curr -> data.vertex, curr -> data.weight);
                }
                curr = curr -> next;
            }
        }
    }

    //Tra ve kq;
    if (d_mst != n) cout << - 1;
    else cout << sum_mst;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    nhap();
    Prim();
    return 0;
}