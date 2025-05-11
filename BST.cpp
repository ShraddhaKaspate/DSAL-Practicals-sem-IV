#include<iostream>
using namespace std;

struct node {
    int data;
    node *L, *R;
};

class BST {
public:
    node* root;
    
    BST() {
        root = NULL;
    }

    void insert(int value);
    void insertNode(node* &root, int value);
    void search(node* root, int key);
    int height(node* root);
    void mirror(node* root);
    void min(node* root);
};

void BST::insert(int value) {
    insertNode(root, value);
}

void BST::insertNode(node* &root, int value) {
    if (root == NULL) {
        root = new node;
        root->data = value;
        root->L = root->R = NULL;
    }
    else if (value < root->data)
        insertNode(root->L, value);
    else
        insertNode(root->R, value);
}

void BST::search(node* root, int key) {
    if (root == NULL) {
        cout << "Key not found\n";
        return;
    }

    if (key == root->data) {
        cout << "Key found\n";
        return;
    }

    if (key < root->data)
        search(root->L, key);
    else
        search(root->R, key);
}

int BST::height(node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->L);
    int rightHeight = height(root->R);
    return max(leftHeight, rightHeight) + 1;  // The +1 is necessary to account for the current node in the height calculation
}

void BST::mirror(node* root) {
    if (root == NULL)
        return;

    node* temp = root->L;
    root->L = root->R;
    root->R = temp;

    mirror(root->L);
    mirror(root->R);
}

void BST::min(node* root) {
    if (root == NULL) {
        cout << "Tree is empty\n";
        return;
    }
    while (root->L != NULL)
        root = root->L;
    cout << "Minimum value is " << root->data << "\n";
}

int main() {
    BST tree;
    int choice, value;
    char ans;

    do {
        cout << "\n1) Insert new node\n2) Number of nodes in longest path\n3) Minimum value\n4) Mirror tree\n5) Search value\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Height (Longest path): " << tree.height(tree.root) << "\n";
                break;
            case 3:
                tree.min(tree.root);
                break;
            case 4:
                tree.mirror(tree.root);
                cout << "Tree after mirror transformation: ";
                break;
            case 5:
                cout << "Enter value to search: ";
                cin >> value;
                tree.search(tree.root, value);
                break;
            default:
                cout << "Invalid choice!\n";
        }

        cout << "Do you want to continue (y/n)? ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    return 0;
}
