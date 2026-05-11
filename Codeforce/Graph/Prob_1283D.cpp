#include <iostream>

using namespace std;

struct Cell{
    int idx;
    bool visited;
    int distance;
    Cell* next;

    Cell(){};
    Cell (int n){
        idx = n;
        visited = false;
        distance = 0;
        next = NULL;
    }
};

long long hashFunc (int n){
    if (n < 0) n = -n;
    long long idx = (1LL * n * 997) % 100003;
    return idx;
}

struct Node{
    Cell* cellAdress;
    Node* next;

    Node(){};
    Node(Cell* c){
        cellAdress = c;
        next = NULL;
    }
};

Cell* findCell (Cell** hashTable, int x)
{
    long long idx = hashFunc (x);
    Cell* curr = hashTable[idx];
    while (curr != NULL){
        if (curr -> idx == x) return curr;
        curr = curr -> next;
    }
    return NULL;
}

Cell* addCell (Cell *&head, int x, int khoang_cach){
    Cell* newCell = new Cell(x);
    newCell -> next = head;
    newCell -> distance = khoang_cach + 1;
    newCell -> visited = true;
    head = newCell;
    
    return newCell;
}

struct Queue{
    Node* front;
    Node* back;
    int size;

    Queue(){
        front = back = NULL;
        size = 0;
    }
    void push (Cell* c){
        Node* newNode = new Node (c);
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
        Cell* address = front -> cellAdress;
        Node* tmp = front;
        front = front -> next;
        delete tmp; tmp = NULL;
        size--;
        return address;
    }

    bool empty(){
        return size == 0;
    }

    Cell* Front(){
        return front -> cellAdress;
    }
};

Queue q;

void bfs (int n, int m, Cell** hashTable, int count, int result[], long long &dist)
{
    while (!q.empty()){
        Cell* curr = q.pop();
        int x1  = curr -> idx + 1;
        int x2 = curr -> idx - 1;
        if (findCell (hashTable, x1) == NULL){
            long long idx = hashFunc (x1);
            Cell* newCell = addCell (hashTable[idx], x1, curr -> distance);
            q.push (newCell);

            dist += newCell -> distance;
            result[count++] = x1;
            if (count == m) return;
        } 
        
        if (findCell (hashTable, x2) == NULL){
            long long idx = hashFunc (x2);
            Cell* newCell = addCell (hashTable[idx], x2, curr -> distance);

            q.push (newCell);
            dist += newCell -> distance;
            result[count++] = x2;
            if (count == m) return;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; 
    cin >> n >> m;
    int tree[n+5];
    Cell* hashTable [100005] = {NULL};

    for (int i = 0; i < n; ++i){
        cin >> tree[i];
        long long idx = hashFunc (tree[i]);
        q.push(addCell(hashTable[idx], tree[i], -1));
    }

    int result[m+5];
    int count = 0;
    long long dist = 0;

    bfs (n, m, hashTable, count, result, dist);

    cout << dist << "\n";
    for (int i = 0; i < m; ++i){
        cout << result[i] << " ";
    }
    return 0;
}