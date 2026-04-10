#include <iostream>
#include <cstring>

using namespace std;
#define ll long long

struct Node{
    char c[36];
    int count = 0;
    Node* next;

    Node(char *s){
        strcpy (c, s);
        count = 0;
        next = NULL;
    }
};

void addNode (Node* &head, char *s){
    Node* newNode = new Node (s);
    newNode -> next = head;
    head = newNode;
}

ll hashFunc (char *s){
    ll p = 31, m = 1e4 + 7;
    ll returnVal = 0;
    for (int i = 0; i < strlen(s); ++i){
        returnVal = (returnVal * p + (ll)s[i]) % m;
        p = (p * 31) % m;
    }

    return returnVal;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    cin.ignore();
    char c[36];
    Node* hashTable [100005] = {NULL};
    for (int i = 0; i < n; ++i){
        cin.getline (c, 36);
        int idx = hashFunc (c);
        Node* curr = hashTable [idx];
        bool newWord = true;
        while (curr != NULL){
            if (strcmp (c, curr -> c) == 0){
                curr -> count  += 1;
                cout << curr -> c << curr -> count << "\n";
                newWord = false;
                break;
            }
            curr = curr -> next;
        }

        if (newWord){
            cout << "OK" << "\n";
            addNode (hashTable[idx], c);
        }
    }
    return 0;
}