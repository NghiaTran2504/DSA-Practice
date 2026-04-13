#include <iostream>

using namespace std;

struct Node{
    int vertex;
    Node* next;

    Node(int val){
        vertex = val;
        next = NULL;
    }
};
struct Graph{
    int n;
    Node** list;
    Node** tail;
    Graph (int num){
        n = num;
        list = new Node*[n+5];
        tail = new Node* [n+5];
        for (int i = 1; i <= n; ++i){
            list[i] = NULL;
            tail[i] = NULL;
        }
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

void addNode2 (Node* &head, int x){
    Node* newNode = new Node (x);
    newNode -> next = head;
    head = newNode;
}
int main(){
    int n, m; cin >> n >> m;
    Graph g (n);
    int deg[n+5]{};

    for (int i = 1; i <= m; ++i){
        int x, y; cin >> x >> y;
        addNode (g.list[x], g.tail[x], y);
        addNode (g.list[y], g.tail[y], x);
        deg[x]++;
        deg[y]++;
    }

    //cout << "Bac cua dinh before: ";
   // for (int i = 1; i <= n; ++i) cout << deg[i] << " ";
    //cout << "\n";
    bool flag = true;
    int groups = 0;
    while (true){
        int count = 0;
        int kick_khoi_lop[1005];
        for (int i = 1; i <= n; ++i){
            if (deg[i] == 1){
                kick_khoi_lop[count++] = i;
                deg[i] = 0;
            }
        }

        if (count == 0) break;
        groups++;

        for (int i = 0; i < count; ++i){
            Node* curr = g.list[kick_khoi_lop[i]];
            while (curr != NULL){
                if (deg[curr -> vertex] > 0)
                    deg[curr -> vertex]--;
                
                curr = curr -> next;
            }
        }
    }

    cout << groups;
    return 0;
}