#include <iostream>

using namespace std;

struct Node{
    int idx;
    Node* next;

    Node (){};
    Node (int x){
        idx = x;
        next = NULL;
    }
};

bool visited[105];

struct Graph{
    int v;
    Node** list;

    Graph (int n){
        v = n;
        list = new Node* [v + 5];
        for (int i = 0; i <= n; ++i){
            list[i] = NULL;
        }
    }

    ~Graph (){
        for (int i = 0; i <= v; ++i){
            Node* curr = list[i];
            while (curr != NULL){
                Node* tmp = curr;
                curr = curr -> next;
                delete tmp;
            }
        }
        delete[] list;
    }
};

void addNode (Node* &head, int idx){
    Node* newNode = new Node (idx);
    newNode -> next = head;
    head = newNode;
}

void dfs(Graph &g, int u)
{
    visited[u] = true;
    Node* curr = g.list[u];
    while (curr != NULL){
        if (!visited[curr -> idx]){
            visited[curr -> idx] = true;
            dfs (g, curr -> idx);
        }
        curr = curr -> next;
    }
}
int main()
{
    int n; cin >> n;
    pair <int, int> p[105];
    Graph g(n);
    for (int i = 1; i <= n; ++i){
        cin >> p[i].first >> p[i].second;
    }

    /*Duyet qua tung phan tu de dua vao adjacency list
        voi cac dinh co gia tri tuong ung voi index trong mang goc*/

    for (int i = 1; i <= n; ++i){
        for (int j = i + 1; j <= n; ++j){
            if (p[j].first == p[i].first || p[j].second == p[i].second){
                addNode (g.list[i], j);
                addNode (g.list[j], i);
            }
        }
    }
    int count = 0;
    for (int i = 1; i <= n; ++i){
        if (!visited[i]){
            dfs (g, i);
            count++;
        }
    }
    cout << count - 1;
    return 0;
}