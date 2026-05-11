#include <iostream>
#include <cstring>

using namespace std;

struct Node{
    char name[1000];
    Node* next;

    Node(char *c){
        strcpy (name, c);
        next = NULL;
    }
};

void addNode (Node* &head, char *name){
    Node* newNode = new Node (name);
    newNode -> next = head;
    head = newNode;
}

long long hashFunc (char *c){
    long long ans = 0, m = 100004;
    for (int i = 0; i < strlen (c); ++i){
        ans = (ans * 31 + (long long)c[i]) % m;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    Node* hashTable[100005] = {NULL};
    char name[105];
    for (int i = 0; i < n; ++i){
        cin >> name;
        long long idx = hashFunc (name);
        Node* curr = hashTable[idx];
        bool existed = false;
            while (curr != NULL){
                if (strcmp (curr -> name, name) == 0){
                    cout << "YES\n";
                    existed = true;
                    break;
                }
                curr = curr -> next;
            }
        if (!existed){
            cout << "NO\n";
            addNode (hashTable[idx], name);
        }
    }
    return 0;
}