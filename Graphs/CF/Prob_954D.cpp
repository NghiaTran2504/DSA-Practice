#include <iostream>
#include <cstring>

using namespace std;

int n, m, s, t;

struct Node{
    int vertex;
    Node* next;

    Node(int val){
        vertex = val;
        next = NULL;
    }
};

struct Graph{
    /* Create an adjacency list as a 2D arrays of linked lists*/
    int n;
    Node** adj_list;
    Node** tail;
    Graph (int num){
        n = num;
        adj_list = new Node* [n + 5];
        tail = new Node* [n+5];
        for (int i = 0; i <= n; ++i){
            adj_list[i] = NULL;
            tail[i] = NULL;
        }
    }

    ~Graph()
    {
        for (int i = 0; i <= n; ++i){
            Node* curr = adj_list[i];
            while (curr != NULL){
                Node* tmp = curr;
                curr = curr -> next;
                delete tmp;
            }
        }
        delete[] adj_list;
    }
};

void addNode (Node* &head, Node* &tail, int x){
    Node* newNode = new Node (x);
    if (head == NULL){
        head = tail = newNode;
    }
    else{
        tail -> next = newNode;
        tail = newNode;
    }
}

struct Queue{
    Node* top;
    Node* back;
    int size;

    Queue(){
        top = NULL;
        back = NULL;
        size = 0;
    }

    void push (int x){
        addNode (top, back, x);
        size += 1;
    }

    void pop(){
        if (top == NULL) return;
        Node* tmp = top;
        top = top -> next;
        delete tmp; tmp = NULL;
        size -= 1;
    }

    bool empty(){
        return size == 0;
    }

    int Front(){
        return top -> vertex;
    }
};

Queue q;
int ds[1005], dt[1005];
bool visited[1005];

void bfs_s (Graph &g, int u){
    q.push (u);
    visited[u] = true;
    ds[u] = 0;
    int dis = 1;

    while (!q.empty()){
        int front = q.Front();
        q.pop();

        Node* curr = g.adj_list[front];
        while (curr != NULL){
            int vertex = curr -> vertex;
            if (!visited[vertex]){
                visited[vertex] = true;
                q.push (vertex);
                ds[vertex] = ds[front] + 1;
            }
            curr = curr -> next;
        }
    }
}

void bfs_t (Graph& g, int u){
    q.push(u);
    visited[u] = true;
    dt[u] = 0;
    int dis = 1;

    while (!q.empty())
    {
        int front = q.Front();
        q.pop();

        Node *curr = g.adj_list[front];
        while (curr != NULL)
        {
            int vertex = curr -> vertex;
            if (!visited[vertex]){
                visited[vertex] = true;
                dt[vertex] = dt[front] + 1;;
                q.push (vertex);
            }
            curr = curr->next;
        }
    }
}

int minn (int a, int b)
{
    if (a <= b) return a;
    return b;
}

void solve(Graph &g, int orignalDist){
    /* Đối với mỗi cặp đỉnh (u,v) chưa có đường nối 
    khi ta tạo 1 đường nối thì đường đi từ s -> t 
    mà phải đi qua cây cầu (u, v) là: 
    min (ds[u] + 1 + dt[v], ds[v] + 1 + dt[u])*/

    /* GT cong thuc: 
        ds[u] + 1 + dt[v] la dis(s --> u) + 1 (qua cau (u,v)) + dis (v --> t)
        ds[v] + 1 + dt[u] la dis (s --> v) + 1 (qua cau (u,v)) + dis (u --> t)*/

    /* Đường nối đó chỉ thỏa yêu cầu đề khi mà
        d_new = min (blah blah) >= d (s --> t) truoc khi xay cau*/
    int ans = 0;
    for (int i = 1; i <= n; ++i){
        for (int j = i + 1; j <= n; ++j){
            Node* curr = g.adj_list[i];
            bool skip = false;
            while (curr != NULL){
                if (curr -> vertex == j){
                    skip = true;
                    break;
                }
                curr = curr -> next;
            }
            if (!skip){
                int newDist = minn (ds[i] + 1 + dt[j], ds[j] + 1 + dt[i]);
                if (newDist >= orignalDist) ans++;
            }
        }
    }
    cout << ans;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m >> s >> t;
    Graph g(n);
    for (int i = 0; i < m; ++i){
        int x, y; 
        cin >> x >> y;
        addNode (g.adj_list[x], g.tail[x], y);
        addNode (g.adj_list[y], g.tail[y], x);
    }

    bfs_s (g, s);
    memset (visited, false, sizeof (bool) * 1005);
    bfs_t (g, t);

    // for (int i = 1; i <= n; ++i){
    //     cout << "Dinh " << i << ": ";
    //     Node* curr = g.adj_list[i];
    //     while (curr != NULL){
    //         cout << curr -> vertex << " ";
    //         curr = curr -> next;
    //     }
    //     cout << "\n";
    // }

    // for (int i = 1; i <= n; ++i) cout << ds[i] << " ";
    // cout << "\n";
    // for (int i = 1; i <= n; ++i) cout << dt[i] << " ";
    
    solve (g, ds[t]);
    return 0;
}