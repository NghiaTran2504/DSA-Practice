#include <iostream>
#include <cstring>

using namespace std;

//DFS voi input la danh sach ke
struct Node{
    int vertex;
    Node* next;
    Node(int val){
        vertex = val;
        next = nullptr;
    }
};

struct Graph{
    int n;
    Node** list;
    Node** tail;

    Graph(int num){
        n = num;
        list = new Node* [n+5];
        tail = new Node* [n+5];
        for (int i = 0; i <= n; ++i)
            list[i] = tail[i] = NULL;
    }

    ~Graph(){
        for (int i = 0; i <= n; ++i){
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

void addEdge (Node* &head, Node* &tail, int val){
    Node* newNode = new Node (val);
    if (head == NULL){
        head = tail = newNode;
    }
    else{
        tail -> next = newNode;
        tail = newNode;
    }
}

void dfs (Graph &g, int u, bool visited[]){
    cout << u << " ";
    visited[u] = true;

    Node* curr = g.list[u];
    while (curr != NULL){
        if (!visited[curr -> vertex])
            dfs (g, curr -> vertex, visited);
        
        curr = curr -> next;
    }
}

// In-direct graph
void inp1 (Graph &g, int n){
    for (int i = 1; i <= n; ++i){
        char* s = new char[n];
        cin.getline (s, 1000);
        
        char* token = strtok (s, " ");
        while (token != NULL){
            int val = atoi (token);
            addEdge (g.list[i], g.tail[i], val);
            token = strtok (NULL," ");
        }
    }
}

// Direct graph
void inp2 (Graph &g, int n){
    for (int i = 1; i <= n; ++i){
        char* s = new char [n];
        cin.getline (s, 1000);
        
        char* token = strtok (s, " ");
        while (token != NULL ){
            int num = atoi (token);
            if (num == 0) break;
            addEdge (g.list[i], g.tail[i], num);
            token = strtok (NULL, " ");
        }
    }
}
int main()
{
    int n; cin >> n;
    cin.ignore();

    Graph g(n);
    bool visited[n+5] = {};
    inp2(g, n);
    dfs (g, 1, visited);
    return 0;
}