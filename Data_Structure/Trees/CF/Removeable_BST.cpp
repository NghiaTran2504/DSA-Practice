#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

struct Node;
Node *createNode(int);
Node *addNode(Node *&, int);
void inorder(Node *);
void preorder(Node *);
void postorder(Node *);
bool existsInBST(Node *, int);
Node *search(Node *, int);
void solve();
Node *deleteNode(Node *, int);
Node *findMin(Node *);
void swapNode(Node *&, Node *&);

struct Node
{
    int val;
    Node *left;
    Node *right;
};

Node *deleteNode(Node *root, int data)
{
    if (root == NULL)
        return root;
    if (data < root->val)
        root->left = deleteNode(root->left, data);
    else if (data > root->val)
        root->right = deleteNode(root->right, data);

    else
    {
        if (root->left == NULL)
        {
            Node *tmp = root->right;
            delete root;
            return tmp;
        }
        else if (root->right == NULL)
        {
            Node *tmp = root->left;
            delete root;
            return tmp;
        }

        Node *tmp = findMin(root->right);
        root->val = tmp->val;
        root->right = deleteNode(root->right, tmp->val);
    }

    return root;
}

Node *findMin(Node *root)
{
    if (root == NULL)
        return root;
    if (root->left == NULL)
        return root;
    else
        return findMin(root->left);
}

Node *search(Node *root, int data)
{
    if (root == NULL)
        return root;
    if (data > root->val)
    {
        return search(root->right, data);
    }
    else if (data < root->val)
    {
        return search(root->left, data);
    }
    else
        return root;
}

void solve()
{
    Node *root = NULL;
    int num;
    while (cin >> num)
    {
        if (num == 1)
        {
            int x;
            cin >> x;
            addNode(root, x);
        }
        else if (num == 2)
        {
            cin.ignore();
            char *c = new char[4];
            cin.getline(c, 5);

            if (strcmp(c, "LNR") == 0)
            {
                inorder(root);
                cout << '\n';
            }
            else if (strcmp(c, "NLR") == 0)
            {
                preorder(root);
                cout << '\n';
            }
            else
            {
                postorder(root);
                cout << '\n';
            }

            delete[] c;
        }

        else if (num == 3)
        {
            int x;
            cin >> x;
            if (search(root, x) == NULL)
                cout << "NO" << '\n';
            else
                cout << "YES" << "\n";
        }
        else
        {
            int x;
            cin >> x;
            root = deleteNode(root, x);
        }
    }
}

Node *createNode(int data)
{
    Node *newNode = new Node;
    newNode->val = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *addNode(Node *&root, int x)
{
    if (root == NULL)
    {
        root = createNode(x);
        return root;
    }

    if (x > root->val)
        return addNode(root->right, x);
    else if (x < root->val)
        return addNode(root->left, x);
    else
        return root;
}

bool existsInBST(Node *root, int x)
{
    if (root == NULL)
        return 0;

    if (x > root->val)
        return existsInBST(root->right, x);
    else if (x < root->val)
        return existsInBST(root->left, x);
    else if (x == root->val)
        return 1;
}

void inorder(Node *root) // LNR
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void preorder(Node *root) // NLR
{
    if (root == NULL)
        return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) // LRN
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}