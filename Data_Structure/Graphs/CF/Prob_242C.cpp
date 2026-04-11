#include <iostream>

using namespace std;

/* Idea: Sử dụng hash table và BFS để tìm đường đi
    - Sử dụng hash table để đánh dấu các ô đi được trong bàn cờ
    - Sau đó từ vị trí đang đứng loang 8 hướng
    - Vị trí nào đi được và đánh dấu đã đi trong hash table
    - Sau khi đánh dấu hết, nếu tọa độ destination được bật --> đi được*/

int dr[] = {0, 0, -1, -1, -1, 1, 1, 1};
int dc[] = {-1, 1, -1, 0, 1, -1, 0, 1};

int x0, y0, x1, y1;
int n;




struct Cell{
    int r, c;
    int step;
    bool visited;
    Cell *next;
    
    Cell(){};
    Cell (int x, int y){
        r = x;
        c = y;
        step = -1;
        visited = false;
        next = NULL;
    }
};

struct Node{
    Cell* cell;
    Node* next;

    Node(){};
    Node (Cell* address){
        cell = address;
        next = NULL;
    }
};


long long hashFunc (int row, int col)
{
    long long idx = (1LL * row * 31337 + col) % 100003;
    return idx;
}

void addCell (Cell* &head, int row, int col){
    Cell* newCell = new Cell (row, col);
    newCell -> next = head;
    head = newCell;
}

struct Queue{
    Node* front;
    Node* back;
    int size;

    Queue(){
        front = back = NULL;
        size = 0;
    }

    void push (Cell* address){
        Node* newNode = new Node (address);
        if (front == NULL){
            front = back = newNode;

        }
        else{
            back -> next = newNode;
            back = newNode;
        }
        size++;
    }

    Cell* pop(){
        if (front == NULL) return NULL;
        Node* curr = front;
        Cell* data = front -> cell;
        front = front -> next;
        delete curr;

        if (front == NULL) back = NULL;
        size--;
        return data;
    }

    bool empty(){
        return size == 0;
    }

};

/* Dung bfs de danh dau cac vi tri di duoc */
Queue q;

Cell* findCell (Cell** mapp, int row, int col)
{
    long long idx = hashFunc (row, col);
    Cell* curr = mapp[idx];
    while (curr != NULL){
        if (curr -> r == row && curr -> c == col) return curr;
        curr = curr -> next;
    }

    return NULL;
}

void bfs (Cell** mapp, int row, int col){
    Cell* start = findCell (mapp, row, col);
    if (start == NULL) return;

    start -> visited = true;
    start -> step = 0;
    q.push (start);

    while (!q.empty()){
        Cell* current = q.pop();

        for (int i = 0; i < 8; ++i){
            int nr = current -> r + dr[i];
            int nc = current -> c + dc[i];
            Cell* nghia = findCell (mapp, nr, nc);

            if (nghia != NULL && !nghia -> visited){
                nghia -> visited = true;
                q.push (nghia);
                nghia -> step = current -> step + 1;
            }
        }
    }
}

int main()
{
    Cell* mapp [100005] = {NULL};
    cin >> x0 >> y0 >> x1 >> y1;
    cin >> n;
    for (int i = 0; i < n; ++i){
        int r, a, b;
        cin >> r >> a >> b;
        for (int j = a; j <= b; ++j){
            if (findCell (mapp, r, j) == NULL){

                long long idx = hashFunc (r, j);
                addCell (mapp[idx], r, j);
            }
        }
    }

    bfs (mapp, x0, y0);

    Cell* curr = findCell (mapp, x1, y1);
    if (curr != NULL && curr -> visited) cout << curr -> step;
    else cout << -1;
    return 0;
}