#include <iostream>
#include <string>

using namespace std;
#define ll long long

int n, m; 

ll hashFunc (string s){
    ll ans = 0;
    ll p = 53;
    for (int i = 0; i < s.size(); ++i){
        ans = (ans * p + (ll)s[i]) % m;
    }

    return ans;
}

struct Node{
    string s;
    int count;
    Node* next;

    Node (string c){
        s = c;
        count = 0;
        next = NULL;
    }
};

void addNode (Node* &head, string s){
    Node* newNode = new Node (s);
    newNode -> next = head;
    if (head == NULL)
        newNode -> count = 1;
    else newNode -> count = head -> count + 1;

    head = newNode;
}

int main()
{
    cin >> n >> m;
    Node *hashTable[m] = {NULL};

    string s;
    for (int i = 0; i < n; ++i){
        cin >> s;
        ll idx = hashFunc (s) % m;
        
        int step = 0;
        while (step < 5 && hashTable[idx] != NULL){
            step++;
            idx = (idx + 1) % m;
        }

        addNode (hashTable[idx], s);
        cout << step << " " << hashTable[idx] ->count -1 << "\n";
    }
    return 0;
}