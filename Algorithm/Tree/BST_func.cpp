#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

int maxx (int a, int b){
    if (a >= b) return a;
    return b;
}
struct Node{
    int key;
    Node* left, *right;

    Node(int val){
        key = val;
        left = right = NULL;
    }
};

void Insert (Node* &pRoot, int x){
    if (pRoot == NULL){
        Node* newNode = new Node (x);
        pRoot = newNode;
        return;
    }

    Node* curr = pRoot;
    Node* parent;

    while (curr != NULL){
        parent = curr;
        if (x < curr -> key) curr = curr -> left;
        else if (x > curr -> key) curr = curr -> right;
        else return;
    }

    if (x < parent -> key) parent -> left = new Node (x);
    else if (x > parent -> key) parent -> right = new Node (x);
}

void LNR (Node* pRoot){
    if (pRoot == NULL) return;

    LNR (pRoot -> left);
    cout << pRoot -> key << " ";
    LNR (pRoot -> right);
}

void NLR (Node* pRoot){
    if (pRoot == NULL) return;

    cout << pRoot -> key << " ";
    NLR (pRoot -> left);
    NLR (pRoot -> right);
}

void LRN (Node* pRoot){
    if (pRoot == NULL) return;

    LRN (pRoot -> left);
    LRN (pRoot -> right);
    cout << pRoot -> key << " ";
}


void levelOrder (Node* pRoot){
    if (pRoot == NULL) return;

    queue <Node*> q;
    q.push (pRoot);
    while (!q.empty()){
        Node* curr = q.front();
        q.pop();
        cout << curr -> key << " ";
        if (curr -> left != NULL) q.push (curr -> left);
        if (curr -> right != NULL) q.push (curr -> right);
    }
}

int Height (Node* pRoot){
    if (pRoot == NULL) return 0;
    int HeightOfLeftSubTree = Height (pRoot -> left);
    int HeightOfRightSubTree = Height (pRoot -> right);

    return 1 + maxx (HeightOfRightSubTree, HeightOfRightSubTree);
}

int countNode (Node* pRoot){
    if (pRoot == NULL) return 0;

    int countLeft = countNode (pRoot -> left);
    int countRight = countNode (pRoot -> right);

    return 1 + countLeft + countRight;
}

int sumNode (Node* pRoot){
    if (pRoot == NULL) return 0;

    int sumLeft = sumNode (pRoot -> left);
    int sumRight = sumNode (pRoot -> right);

    return pRoot -> key + sumLeft + sumRight;
}

int countLeaf (Node* pRoot){
    if (pRoot == NULL) return 0;

    int countLeft = countLeaf (pRoot -> left);
    int countRight = countLeaf (pRoot -> right);

    if (countLeft == 0 && countRight == 0) return 1;

    return countLeft + countRight;
}

int SumEvenNode (Node* pRoot){
    if (pRoot == NULL) return 0;

    int sumLeft = SumEvenNode (pRoot -> left);
    int sumRight = SumEvenNode (pRoot -> right);

    if (pRoot -> key % 2 == 0) return pRoot -> key + sumLeft + sumRight;
    else return sumLeft + sumRight;
}

Node* Search (Node* pRoot, int x){
    if (pRoot == NULL) return NULL;

    Node* curr = pRoot;
    while (curr != NULL){
        if (curr -> key > x)
            curr = curr -> left;
        else if (curr -> key < x)
            curr = curr -> right;
        else return curr;
    }
}

Node* findMin (Node* pRoot){
    if (pRoot == NULL) return;

    Node* curr = pRoot;
    while (curr != NULL){
        if (curr -> left == NULL) return curr;
        curr = curr -> left;
    }
}

Node* deleteNode (Node*& pRoot, int x){
    if (pRoot == NULL) return;

    if (pRoot -> key < x)
        pRoot -> right = deleteNode (pRoot -> right, x);
    else if (pRoot -> key > x)
        pRoot -> left = deleteNode (pRoot -> left, x);

    else{
        if (pRoot -> right == NULL){
            Node* tmp = pRoot -> left;
            delete pRoot;
            return tmp;
        }
        else if (pRoot -> left == NULL){
            Node* tmp = pRoot -> right;
            delete pRoot;
            return tmp;
        }
        else{
            Node* successor = findMin (pRoot -> right);
            pRoot -> key = successor -> key;
            pRoot -> right = deleteNode (pRoot -> right, successor -> key);
        }
    }

    return pRoot;
}

