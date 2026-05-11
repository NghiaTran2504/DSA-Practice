#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int vertex;
    Node* next;
    
    Node(int v){
        vertex = v;
        next = NULL;
    }
};

struct Graph{
    int n;
    Node** adj;
    Node** tail;

    Graph(int num){
        n = num;
        adj = new Node*[n+5];
        tail = new Node*[n+5];

        for (int i = 0; i <= n; ++i){
            adj[i] = tail[i] = nullptr;
        }
    }
};

void addEdge (Graph &g, int u, int v){
    Node* newNode = new Node (u);
    if (g.adj[v] == NULL){
        g.adj[v] = g.tail[v] = newNode;
    }
    else{
        g.tail[v] -> next = newNode;
        g.tail[v] = newNode;
    }

    Node* newNode2 = new Node (v);
    if (g.adj[u] == NULL){
        g.adj[u] = g.tail[u] = newNode2;
    }
    else{
        g.tail[u] -> next = newNode2;
        g.tail[u] = newNode2;
    }
}

//CACH KHO DAM
void printList (int n, int m){
    Graph g(n);

    for (int i = 0; i < m; ++i){
        int x, y; 
        cin >> x >> y;
        addEdge(g, x, y);
    }

    for (int i = 1; i <= n; ++i){
        cout << i << ": { ";
        Node* curr = g.adj[i];
        while (curr != NULL){
            cout << curr -> vertex << " ";
            curr = curr -> next;
        }
        cout << "}\n";
    }
}

void printList_Vip (int n, int m){
    vector <int> v[n+5];
    for (int i = 0; i < m; ++i){
        int x, y; 
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    for (int i = 1; i <= n; ++i)
    {
        cout << i << ": { ";
        for (auto x : v[i]) cout << x << " "; 
        cout << "}\n";
    }
}
int main(){
    int n, m;
    cin >> n >> m;
    printList_Vip(n, m);
    return 0;
}