#include <iostream>

using namespace std;

struct Node
{
    int vertex;
    Node *next;

    Node(int val)
    {
        vertex = val;
        next = NULL;
    }
};

struct Graph
{
    int n;
    Node **list;
    Node **tail;
    Graph(int num)
    {
        n = num;
        list = new Node *[n + 5];
        tail = new Node *[n + 5];
        for (int i = 0; i <= n; ++i)
            list[i] = tail[i] = NULL;
    }

    ~Graph()
    {
        for (int i = 0; i <= n; ++i)
        {
            Node *curr = list[i];
            while (curr != NULL)
            {
                Node *tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }

        delete[] list;
    }
};

void addEdge(Node *&head, Node *&tail, int val)
{
    Node *newNode = new Node(val);
    if (head == NULL)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void deleteFirst (Node* &head, Node* &tail){
    if (head == NULL) return;
    Node* curr = head;
    head = head -> next;
    delete curr;

    if (head == NULL) tail = NULL;
}

struct Queue{
    Node* front, *back;
    int size;

    Queue (){
        front = back = NULL;
        size = 0;
    }

    void push (int val){
        addEdge(front, back, val);
        size++;
    }

    void pop(){
        deleteFirst(front,back);
        size--;
    }
    bool empty(){
        return size == 0;
    }
    
};

void inp(Graph &g, int n, int m){
    for (int i = 1; i <= m; ++i){
        int x, y; cin >> x >> y;
        addEdge (g.list[x], g.tail[x], y);
        addEdge (g.list[y], g.tail[y], x);
    }
}

void bfs (Graph &g, int u, bool visited[], int n){
    Queue q;
    q.push (u);
    visited[u] = true;

    while (!q.empty()){
        int v = q.front -> vertex;
        q.pop();
        cout << v << " ";
        Node* curr = g.list[v];
        while (curr != NULL){
            if (!visited[curr -> vertex]){
                visited[curr -> vertex] = true;
                q.push (curr -> vertex);
            }
            curr = curr -> next;
        }
    }
}
int main(){
    int n, m;
    cin >> n >> m;
    Graph g(n);
    inp (g, n, m);
    bool visited[n+5]{};
    bfs (g, 1, visited, n);
    return 0;
}