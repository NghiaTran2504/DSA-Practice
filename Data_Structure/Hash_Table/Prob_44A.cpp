#include <iostream>
#include <cstring>
using namespace std;

struct Node{
    char Tree[100];
    char Color[100];
    Node* next;

    Node(char *tree, char* color){
        strcpy (Tree, tree);
        strcpy (Color, color);
        next = NULL;
    }
};

void addNode(Node* &head, char* tree, char* color){
    Node* newNode = new Node(tree, color);
    newNode -> next = head;
    head = newNode;
}

long long hashFunc (char *c)
{
    long long ans = 0;
    long long p = 31, m = 100003;
    for (int i = 0; i < strlen (c); ++i){
        ans = (ans * p + (long long)c[i]) % m;
    }

    return ans;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n; cin >> n;
    int count = 0;
    Node* hashTable[100005] = {NULL};
    char tree[100];
    char color[100];
    for (int i = 0; i < n; ++i){
        cin >> tree >> color;
        long long idx = hashFunc (tree);

        Node* curr = hashTable[idx];
        while (curr != NULL){
            if (strcmp (curr -> Tree, tree) == 0 && strcmp (curr -> Color, color) == 0){
                count --;
                break;
            }
            curr = curr -> next;
        }
        count++;
        addNode (hashTable[idx], tree, color);
    }

    cout << count << "\n";
    return 0;
}