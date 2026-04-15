#include <iostream>
#include <string>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;

    Node (int val){
        key = val;
        left = right = NULL;
    }
};

Node* Insert (Node* & root, int x){
    if (root == NULL) {
        Node* newNode = new Node (x);
        root = newNode;

        return root;
    }    
    else if (x < root -> key){
        return Insert (root -> left, x);
    }
    else if (x > root -> key){
        return Insert (root -> right, x);
    }
    else{
        return root;
    }
}

void LNR (Node* root){
    if (root == NULL) return;
    LNR (root -> left);
    cout << root -> key << " ";
    LNR (root -> right);
}

void NLR (Node *root){
    if (root == NULL) return;
    cout << root -> key << " ";
    NLR (root -> left);
    NLR (root -> right);
}

void LRN (Node* root){
    if (root == NULL) return;
    LRN (root -> left);
    LRN (root -> right);
    cout << root -> key << " ";
}

Node *Search (Node* root, int x){
    if (root == NULL) return NULL;

    Node* curr = root;
    while (curr != NULL){
        if (curr -> key == x) break;
        else if (curr -> key > x){
            curr = curr -> left;
        }
        else curr = curr -> right;
    }

    return curr;
}

Node* findMin (Node* root){
    if (root == NULL) return NULL;

    Node* curr = root;
    while (curr != NULL){
        if (curr -> left == NULL) break;
        else curr = curr -> left;
    }
    return curr;
}

Node* deleteNode (Node* root, int x){
    if (root == NULL) return NULL;

    if (root -> key > x){
        root -> left = deleteNode (root -> left, x);
    }
    else if (root -> key < x){
        root -> right = deleteNode (root -> right, x);
    }

    else{
        if (root -> right == NULL){
            Node* tmp = root -> left;
            delete root;
            return tmp;
        }
        if (root -> left == NULL){
            Node* tmp = root -> right;
            delete root;
            return tmp;
        }
        else{
            Node* successor = findMin (root -> right);
            root -> key = successor -> key;
            root -> right = deleteNode (root -> right, successor -> key);
        }
    }
    return root;
}
int main()
{
    int n; 
    Node* root = NULL;
    while (cin >> n){
        switch (n){
            case 1:{
                int x; cin >> x;
                Insert (root, x);
                break;
            }
            case 2:{
                string s;
                cin >> s;
                if (s == "LNR") 
                    LNR (root);
                else if (s == "NLR")
                    NLR (root);
                else LRN (root);

                cout << "\n";
                break;
            }
            case 3:{
                int x; cin >> x;
                Node* find = Search (root, x);
                if (find == NULL) cout << "NO\n";
                else cout << "YES\n";

                break;
            }
            case 4:{
                int x; cin >> x;
                root = deleteNode (root, x);
                break;
            }

            default: break;
        }
    }
    return 0;
}