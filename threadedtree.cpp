#include <iostream>
using namespace std;

// Structure for a tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    bool rightThread; // true if right pointer is a thread

    Node(int val) : data(val), left(nullptr), right(nullptr), rightThread(false) {}
};

// Function to perform inorder traversal and set threads
void convertToThreaded(Node* root, Node*& prev) {
    if (!root) return;

    // Recur for the left subtree
    convertToThreaded(root->left, prev);

    // If the previous node is not null, set the right thread
    if (prev && prev->right == nullptr) {
        prev->right = root; // Set the right pointer to the current node
        prev->rightThread = true; // Mark it as a thread
    }

    // Update the previous node to the current node
    prev = root;

    // Recur for the right subtree
    convertToThreaded(root->right, prev);
}

// Function to convert a binary tree to a threaded binary tree
void convertToThreadedBinaryTree(Node* root) {
    Node* prev = nullptr; // Previous node in inorder traversal
    convertToThreaded(root, prev);
}

// Function to print inorder traversal of the threaded binary tree
void inorderTraversal(Node* root) {
    Node* current = root;

    // Go to the leftmost node
    while (current->left) {
        current = current->left;
    }

    // Traverse the threaded binary tree
    while (current) {
        cout << current->data << " "; // Print the current node

        // If the right pointer is a thread, follow the thread
        if (current->rightThread) {
            current = current->right; // Move to the inorder successor
        } else {
            current = current->right; // Move to the right child
            // Go to the leftmost node of the right subtree
            while (current && current->left) {
                current = current->left;
            }
        }
    }
}

int main() {
    // Create a simple binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    // Convert to threaded binary tree
    convertToThreadedBinaryTree(root);

    // Print inorder traversal of the threaded binary tree
    cout << "Inorder traversal of the threaded binary tree: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}