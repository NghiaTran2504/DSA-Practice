#include <iostream>
#include <string>

using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;

    Node (int x){
        val = x;
        left = right = NULL;
    }
};

void addNode (Node* &head, int x){
    if (head == NULL){
        Node* newNode = new Node (x);
        head = newNode;
        return;
    }
    else if (x < head -> val){
        addNode (head -> left, x);
    }
    else if (x > head -> val){
        addNode (head -> right, x);
    }
    else return;
}

bool existsInBST(Node *root, int x) {
    if (root == NULL) return false;

    if (x < root -> val) 
        return existsInBST (root -> left, x);
    else if (x > root -> val)
        return existsInBST (root -> right, x);
    else return true;
}

void inOrder (Node* root){
    if (root == NULL) return;

    inOrder (root -> left);
    cout << root -> val << " ";
    inOrder (root -> right);

}

void preOrder (Node* root){
    if (root == NULL) return;
    
    cout << root -> val << " ";
    preOrder (root -> left);
    preOrder (root -> right);

}

void postOrder (Node* root){
    if (root == NULL) return;

    postOrder (root -> left);
    postOrder (root -> right);
    cout << root -> val << " ";
}

void solve(){
    int n;
    Node* root = NULL;
    while (cin >> n){
        switch (n){
            case 1:{
                int x; cin >> x;
                addNode (root, x);
                break;
            }
            case 2:{
                cin.ignore();
                string s; cin >> s;
                if (s == "LNR"){
                    inOrder(root);
                    cout << "\n";
                }
                else if (s == "NLR"){
                    preOrder (root);
                    cout << "\n";
                }
                else{
                    postOrder (root);
                    cout << "\n";
                }
                break;
            }
            case 3:{
                int x; cin >> x;
                if (existsInBST(root, x)) cout << "YES\n";
                else cout << "NO\n";
                break;
            }
            default: 
                break;
        }
    }
}
int main()
{
    solve();
    return 0;
}