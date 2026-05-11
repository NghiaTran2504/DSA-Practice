#include <iostream>
#include <vector>

using namespace std;

// BIEU DIEN DO THI TU MA TRAN KE SANG:
// DANH SACH KE, DANH SACH CANH
struct Node{
    int vertex;
    Node* next;

    Node (int v){
        vertex = v;
        next = NULL;
    }
};

struct Graph{
    int n;
    Node** adj;
    Node** tail;

    Graph (int num){
        n = num;
        adj = new Node* [n+5];
        tail = new Node* [n + 5];
        for (int i = 0; i <= n; ++i){
            adj[i] = tail[i] = nullptr;
        }
    }

    ~Graph(){
        for (int i = 1; i <= n; ++i)
        {
            Node *curr = adj[i];
            while (curr != nullptr)
            {
                Node *tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }

        delete[] adj;
        delete[] tail;
    }
};

void addEdge(Graph &g, int u, int v){
    Node* newNode = new Node (u);
    if (g.adj[v] == NULL){
        g.adj[v] = g.tail[v] = newNode;
    }
    else{
        g.tail[v] -> next = newNode;
        g.tail[v] = newNode;
    }
}

void Adj_List (int n){
    cin >> n;
    int a[n+5][n+5]{};
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j];
    }

    Graph g(n);

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            if (a[i][j] == 1) addEdge(g, j, i);
        }
    }

    for (int i = 1; i <= n; ++i){
        cout << i << ": ";
        Node* curr = g.adj[i];
        while (curr != NULL){
            cout << curr -> vertex << " ";
            curr = curr -> next;
        }
        cout << "\n";
    }

}
void EdgeList(int n){
    cin >> n;
    int a[n  + 5][n + 5]{};
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j)
        cin >> a[i][j];
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        if (a[i][j] == 1){
            if (i <= j) cout << i << " " << j << "\n";
        }
    }
}

int main()
{
    int n;
    Adj_List (n);
    return 0;
}