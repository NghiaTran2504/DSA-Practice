#include <iostream>

using namespace std;

struct Pair{
    int x;
    int y;
};

struct Node{
    Pair coordinate;
    Node * next;
    Node (Pair p){
        coordinate = p;
        next = NULL;
    }
};

void addBack (Node* &front, Node* &back, Pair p){
    Node* newNode = new Node (p);
    if (front == NULL){
        front = back = newNode;
    }
    else{
        back -> next = newNode;
        back = newNode;
    }
}

void deleteFirst (Node* &front, Node* &back){
    if (front == NULL) return;
    if (front -> next == NULL){
        delete front;
        front = back = NULL;
    }
    else{
        Node* tmp = front;
        front = front -> next;
        delete tmp;
    }
}
struct Queue{
    Node* front, *back;
    int size;
    Queue(){
        front = back = NULL;
        size = 0;
    }
    void push (Pair p){
        addBack (front, back, p);
        size++;
    }
    void pop(){
        deleteFirst (front, back);
        size--;
    }

    bool empty (){
        return size == 0;
    }

    Pair Front(){
        return front -> coordinate;
    }

    ~Queue(){
        Node* curr = front;
        while (curr != NULL){
            Node* tmp = curr;
            curr = curr -> next;
            delete tmp;
        }
    }
};

void bfs(int dx[], int dy[], int** a, int n, int m, int row, int col, long long& sum){
    Queue q;
    Pair p;
    p.x = row;
    p.y = col;

    q.push (p);
    sum += a[p.x][p.y];
    a[p.x][p.y] = 0;

    while (!q.empty()){
        // do sth
        Pair curr = q.Front();
        q.pop();

        //tranversal
        for (int i = 0; i < 4; ++i){
            Pair next;
            next.x = curr.x + dx[i];
            next.y = curr.y + dy[i];
            if (next.x >= 1 && next.x <= n && next.y >= 1 && next.y <= m){
                if (a[next.x][next.y] > 0){
                    sum += a[next.x][next.y];
                    a[next.x][next.y] = 0;
                    q.push (next);
                }
            }
        }
    }
}
long long maxx (long long a, long long b)
{
    if (a >= b) return a;
    return b;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int t; cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        int ** a = new int *[n+5];
        for (int i = 1; i <= n; ++i){
            a[i] = new int[m+5];
        }
        
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                cin >> a[i][j];
            }
        }

        long long ans = 0;
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                long long sum = 0;
                if (a[i][j] > 0){
                    bfs (dx, dy, a, n, m, i, j, sum);
                }
                ans = maxx (ans, sum);
            }
        }

        cout << ans << "\n";

        for (int i = 1; i <= n; ++i){
            delete[] a[i];
        }
        delete[] a;
    }
    return 0;
}