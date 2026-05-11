#include <iostream>
#include <cstring>

using namespace std;
#define ll long long

ll hashFunc (char* c){
    ll p = 31, m = 100003;
    ll hash = 0;
    for (int i = 0; i < strlen (c); ++i){
        hash = (hash * 31 + (ll)c[i]) % m;
    }
    return hash;
}

struct Node{
    char nodeName[100];
    char nodeIp [100];
    Node* next;

    Node(char *sever, char *ip){
        strcpy (nodeName, sever);
        strcpy (nodeIp, ip);
        next = NULL;
    }
};

void addNode(Node* &head, char* server, char* ip){
    Node* newNode = new Node (server, ip);
    newNode -> next = head;
    head = newNode;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    Node *hashTable[100005] = {NULL};
    for (int i = 0; i < n; ++i){
        char name[36];
        char ip[36];
        cin >> name >> ip;

        ll idx = hashFunc (ip);
        addNode (hashTable[idx], name, ip);
    }
   // cout << hashTable[11843]-> nodeName << " " << hashTable[77802] -> nodeName << "\n";
    for (int i = 0; i < m; ++i){
        char name[36];
        char ip[36];

        cin >> name >> ip;
        ip [strlen(ip) - 1] = '\0';

        ll idx = hashFunc (ip);
       // cout << idx << " ";
        Node* curr = hashTable [idx];
        while (curr != NULL){
            if (strcmp (curr -> nodeIp,ip) == 0) {
                cout << name << " " << ip  << "; #" << curr -> nodeName << "\n";
                break; 
            }
            curr = curr -> next;
        }
    }
    return 0;
}