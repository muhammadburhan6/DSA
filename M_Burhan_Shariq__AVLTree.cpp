#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Node {
public:
    int key, height;
    Node *left, *right;
    Node(int k) {
        key = k;
        height = 1;
        left = right = NULL;
    }
};

class AVLTree {
public:
    int getHeight(Node* root) {
        return root ? root->height : 0;
    }

    int getBalance(Node* root) {
        return root ? getHeight(root->left) - getHeight(root->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* root, int key) {
        // Normal BST insertion
        if (!root) return new Node(key);
        if (key < root->key)
            root->left = insert(root->left, key);
        else if (key > root->key)
            root->right = insert(root->right, key);
        else
            return root; // Duplicate keys not allowed

        // Update height
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Get balance factor
        int balance = getBalance(root);

        // Balancing cases
        // Left Left
        if (balance > 1 && key < root->left->key)
            return rotateRight(root);

        // Right Right
        if (balance < -1 && key > root->right->key)
            return rotateLeft(root);

        // Left Right
        if (balance > 1 && key > root->left->key) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Left
        if (balance < -1 && key < root->right->key) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

    void levelorder(Node* root) {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            cout << node->key << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }

    // Bonus: Print tree in visual rotated form
    void printTree(Node* root, int space = 0, int gap = 5) {
        if (!root) return;

        // Increase distance between levels
        space += gap;

        // Print right subtree first
        printTree(root->right, space);

        // Print current node after spaces
        cout << endl;
        for (int i = gap; i < space; i++) cout << " ";
        cout << root->key;

        // Print left subtree
        printTree(root->left, space);
    }
};

int main() {
    AVLTree tree;
    Node* root = NULL;
    int keys[] = {10, 20, 30, 40, 50, 25};

    // Insert keys one by one
    for (int k : keys)
        root = tree.insert(root, k);

    cout << "In-order Traversal: ";
    tree.inorder(root);

    cout << "\nLevel-order Traversal: ";
    tree.levelorder(root);

    cout << "\nVisual Tree (rotated): \n";
    tree.printTree(root);

    return 0;
}
