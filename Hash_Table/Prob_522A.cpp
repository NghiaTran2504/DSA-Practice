#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct Node{
    char name[100];
    int ID;
    Node* next;
    Node (char* s){
        strcpy (name, s);
        next = NULL;
    }
};

struct List{
    int vertex;
    List* next;

    List (int n){
        vertex = n;
        next = NULL;
    }
};

struct Graph{
    int v;
    List** list;
    List** tail;

    Graph (int n){
        v = n;
        list = new List* [v + 5];
        tail = new List* [v + 5];
        for (int i = 0; i <= n; ++i){
            list[i] = NULL;
            tail[i] = NULL;
        }
    }

    void addList (List* &head, List* &tail, int num){
        List* newNode = new List (num);
        if (head == NULL){
            head = tail = newNode;
        }
        else{
            tail -> next = newNode;
            tail = newNode;
        }
    }

    ~Graph ()
    {
        for (int i = 0; i <= v; ++i){
            List* curr = list[i];
            while (curr != NULL){
                List* tmp = curr;
                curr = curr -> next;
                delete tmp;
            }
        }
        delete[] list;
    }
};

/* Polynomial hash function */
long long hashFunc (char *c){
    long long ans = 0;
    long long p =  53, m = 1e5 + 3;
    for (int i = 0; i < strlen (c); ++i){
        ans = (ans * p + (long long)c[i]) % m;
    }

    return ans;
}

/* Them phan tu vao hash table & xu ly trung lap */
void addNode (Node* &head, char* c, int& current_ID){
    Node* newNode = new Node (c);
    newNode -> ID = current_ID;
    current_ID++;
    newNode -> next = head;
    head = newNode;
}

int getID (char* c, Node* hashTable[], int& current_ID){
    long long idx = hashFunc (c);
    Node* curr = hashTable [idx];

    //Check xem chuoi da ton tai trong hash table chua
    while (curr != NULL){
        if (strcmp (curr -> name, c) == 0) return curr -> ID;
        curr = curr -> next;
    }
    
    addNode (hashTable[idx], c, current_ID);

    return current_ID - 1;
}

// O(n)
void lowerCase (char c[]){
    for (int i = 0; i < strlen (c); ++i){
        c[i] = tolower (c[i]);
    }
}

int maxx (int& a, int &b){
    if (a >= b) return a;
    return b;
}
int dfs (Graph &g, int u)
{
    int max_depth = 0;

    List* curr = g.list[u];

    while (curr != NULL){
        int deep = dfs (g, curr -> vertex);
        max_depth = maxx (max_depth, deep);

        curr = curr -> next;
    }
    return max_depth + 1;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    Graph g(2 * n);
    char name1 [100], rac [100], name2[100];
    Node* hashTable[100005] = {NULL};
    int current_ID = 0;

    for (int i = 0; i < n; ++i){
        cin >> name1 >> rac >> name2;
        lowerCase (name1); lowerCase (name2);

        int id2 = getID (name2, hashTable, current_ID);
        int id1 = getID (name1, hashTable, current_ID);

        g.addList (g.list[id2], g.tail[id2], id1);
    }

    cout << dfs (g, 0);
    return 0;
}