#include <iostream>
#include <stack> 
#include <queue>
#include <algorithm>
using namespace std;

// HAPPY CODING
struct Node{
    int key;
    Node* left, *right;
    int height;

    Node (int data){
        key = data;
        left = right = NULL;
        height = 1;
    }
};

int getHeight (Node* p){
    if (p == NULL) return 0;
    return p -> height;
}

int getBalance (Node* pRoot){
    return getHeight (pRoot -> left)  - getHeight (pRoot -> right);
}

Node* rightRotation (Node* pRoot){
    Node* x = pRoot -> left;
    Node* T2 = x -> right;

    x -> right = pRoot;
    pRoot -> left = T2;

    pRoot -> height = 1 + max (getHeight (pRoot -> right), getHeight (pRoot -> left));
    x -> height = 1 + max (getHeight (pRoot -> left), getHeight (pRoot -> right));

    return x;
}

Node* leftRotation (Node* pRoot){
    Node* x = pRoot -> right;
    Node* T2 = x -> left;

    x -> left = pRoot;
    pRoot -> right = T2;

    pRoot -> height = 1 + max (getHeight (pRoot -> right), getHeight(pRoot -> left));
    x -> height = 1 + max (getHeight (pRoot -> left), getHeight (pRoot -> right));

    return x;
}

void Insert (Node* &pRoot, int x){
    if (pRoot == NULL){
        Node* newNode = new Node (x);
        pRoot = newNode;
        return;
    }

    if (x < pRoot -> key) Insert (pRoot -> left, x);
    else if (x > pRoot -> key) Insert (pRoot -> right, x);
    else return;

    pRoot -> height = 1 + max (getHeight (pRoot -> left), getHeight (pRoot -> right));

    int balance = getBalance (pRoot);

    // Lech trai - trai
    if (balance > 1 && x < pRoot -> left -> key){
        pRoot = rightRotation (pRoot);
    }
    
    // Lech phai - phai
    if (balance < -1 && x > pRoot -> right -> key){
        pRoot = leftRotation (pRoot);
    }

    // Lech trai - phai
    if (balance > 1 && x > pRoot -> left -> key){
        pRoot -> left = leftRotation (pRoot -> left);
        pRoot = rightRotation (pRoot);
    }

    // Lech phai - trai
    if (balance < -1 && x < pRoot -> right -> key){
        pRoot -> right = rightRotation (pRoot -> right);
        pRoot = leftRotation (pRoot);
    }
}

bool isAVL (Node* pRoot){
    if (pRoot == NULL) return true;

    int balance = getBalance (pRoot);

    if (abs (balance) <= 1 && isAVL (pRoot -> left) && isAVL (pRoot -> right))
        return true;
    
    return false;
}

Node* findMin (Node* pRoot){
    if (pRoot == NULL) return NULL;

    Node* curr = pRoot;
    while (curr != NULL){
        if (curr -> left == NULL) return curr;
        curr = curr -> left;
    }
}

Node* Remove (Node* &pRoot, int x){
    if (pRoot == NULL) return NULL;

    if (x < pRoot -> key)
        pRoot -> left = Remove (pRoot -> left, x);
    else if (x > pRoot -> key){
        pRoot -> right = Remove (pRoot -> right, x);
    }
    else{
        if (pRoot -> left == NULL || pRoot -> right == NULL){
            Node * tmp = pRoot -> left ? pRoot -> left : pRoot -> right;

            // Vo sinh
            if (tmp == NULL){
                tmp = pRoot;
                pRoot = NULL;
            }
            else{
                *pRoot = *tmp;
            }

            delete tmp;
        }

        else{
            Node* tmp = findMin (pRoot -> right);
            *pRoot = *tmp;
            pRoot -> right = Remove (pRoot -> right, tmp -> key);
        }
    }

    if (pRoot == NULL) return;

    pRoot -> height = 1 + max (getHeight (pRoot -> left), getHeight (pRoot -> right));

    int balance = getBalance (pRoot);

    // Lech trai - trai
    if (balance > 1 && x < pRoot->left->key)
    {
        return rightRotation(pRoot);
    }

    // Lech phai - phai
    if (balance < -1 && x > pRoot->right->key)
    {
        return leftRotation(pRoot);
    }

    // Lech trai - phai
    if (balance > 1 && x > pRoot->left->key)
    {
        pRoot->left = leftRotation(pRoot->left);
        return rightRotation(pRoot);
    }

    // Lech phai - trai
    if (balance < -1 && x < pRoot->right->key)
    {
        pRoot->right = rightRotation(pRoot->right);
        return leftRotation(pRoot);
    }
}
int main()
{

    return 0;
}