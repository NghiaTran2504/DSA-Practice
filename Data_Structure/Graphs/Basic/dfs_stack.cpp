#include <iostream>
#include <cstring>

using namespace std;
struct Node{
    int vertex;
    Node* next;

    Node (int val){
        vertex = val;
        next = NULL;
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

    ~Graph (){
        for (int i = 0; i <= n; ++i){
            Node * curr = list[i];
            while (curr != NULL){
                Node* tmp = curr;
                curr = curr -> next;
                delete tmp;
            }
        }

        delete[] list;
    }
};

void addEdge( Node* &head, Node* &tail, int val){
    Node* newNode = new Node (val);
    if (head == NULL){
        head = tail = newNode;
    }

    else{
        tail -> next = newNode;
        tail = newNode;
    }
}

void addNode (Node* &head, int val){
    Node* newNode = new Node (val);
    newNode -> next = head;
    head = newNode;
}

void deleteNode (Node*& head){
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
    void push (int val){
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
    int Top(){
        return top -> vertex;
    }
    void print(){
        Node* curr = top;
        cout << "Stack tai thoi diem hien tai la: ";
        while (curr != NULL){
            cout << curr -> vertex << " ";
            curr = curr -> next;
        }
        cout << "\n";
    }
};

void readInput (Graph&g){
    cin.ignore();
    for (int i = 1; i <= g.n; ++i){
        char* s = new char[g.n+5];
        cin.getline (s, 1000);
        
        char* token = strtok (s, " ");
        while (token != NULL){
            int num = atoi (token);
            addEdge (g.list[i], g.tail[i], num);
            token = strtok (NULL, " ");
        }

        delete[] s;
    }
}   

void reverseLL (Node* &head){
    if (head == NULL || head -> next == NULL) return;
    Node* dummy = NULL;
    while (head != NULL){
        Node* tmp = head -> next;
        head -> next = dummy;
        dummy = head;
        head = tmp;
    }

    head = dummy;
}
void dfs (Graph& g, int u, bool visited[], int n){
    Stack st;
    st.push (u);
    while (!st.empty()){
        int v = st.Top();
        if (visited[v] == false){
            visited[v] = true;
            cout << v << " ";
            st.pop();
            reverseLL(g.list[v]);
            Node* curr = g.list[v];
            while (curr != NULL){
                st.push (curr -> vertex);
                curr = curr -> next;    
            }
        }
        else st.pop();
    }
}
int main()
{
    int n; cin >> n;
    Graph g(n);
    readInput (g);
    bool visited[n+5]{};
    dfs (g, 1, visited, n);
    return 0;
}