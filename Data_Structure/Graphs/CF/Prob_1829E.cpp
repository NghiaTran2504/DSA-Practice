#include <iostream>

using namespace std;

struct Pair{
    int x;
    int y;
};

struct Node{
    Pair coordinate;
    Node* next;
    Node (int x, int y){
        coordinate.x = x;
        coordinate.y = y;
        next = NULL;
    }
};
void addNode (Node* &head, Pair val){
    Node* newNode = new Node (val.x, val.y);
    newNode -> next = head;
    head = newNode;
}

void deleteNode (Node* &head){
    if (head == NULL) return;
    Node* tmp = head;
    head = head -> next;
    delete tmp;
}

struct Stack{
    Node* top;
    int size;
    Stack(){
        top = NULL;
        size = 0;
    }
    void push(Pair val){
        addNode (top, val);
        size++;
    }
    void pop(){
        deleteNode (top);
        size--;
    }
    bool empty(){
        return size == 0;
    }
    void print(){
        Node* curr = top;
        cout << "Stack hien tai la: ";
        while (curr != NULL){
            cout << "{" << curr ->coordinate.x << ", " << curr -> coordinate.y << "}, ";
            curr = curr -> next;
        }
        cout << "\n";
    }

    Pair Top(){
        return top -> coordinate;
    }
};

long long maxx (long long a, long long b){
    if (a >= b) return a;
    else return b;
}

void dfs (int dx[], int dy[], long long &vol, int row, int col, int** mat, int n, int m){
    Stack st;
    Pair curr;
    curr.x = row; 
    curr.y = col;
    st.push (curr);
    vol += mat[curr.x][curr.y];
    mat[curr.x][curr.y] = 0;

    while (!st.empty()){
        curr = st.Top();
        st.pop();

        Pair nxt;
        for (int i = 0; i < 4; ++i){
            nxt.x = curr.x + dx[i];
            nxt.y = curr.y + dy[i];
            if (nxt.x >= 1 && nxt.x <= n && nxt.y >= 1 && nxt.y <= m){
                if (mat[nxt.x][nxt.y] > 0){
                    
                    vol += mat[nxt.x][nxt.y];
                    st.push (nxt);
                    mat[nxt.x][nxt.y] = 0;
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        int** mat = new int* [n + 5];
        for (int i = 1; i <= n; ++i){
            mat[i] = new int[m + 5]{};
        }

        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j)
                cin >> mat[i][j];
        }

        long long max_vol = 0;
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                long long val = 0;
                if (mat[i][j] > 0) dfs (dx, dy, val, i, j, mat, n, m);
                max_vol = maxx (max_vol, val);
            }
        }

        cout << max_vol << "\n";

        for (int i = 1; i <= n; ++i){
            delete[] mat[i];
        }
        delete[] mat;
    }
}