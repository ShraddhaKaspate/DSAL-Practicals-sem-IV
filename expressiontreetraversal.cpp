#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Tree node structure
struct Node {
    char val;
    Node* left, *right;
    Node(char x) : val(x), left(nullptr), right(nullptr) {}
};

// Return precedence of operators
int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
string infixToPostfix(const string& infix) {
    stack<char> st;
    string post;
    for (char ch : infix) {
        if (isalnum(ch)) {
            post += ch;
        } else {
            while (!st.empty() && prec(st.top()) >= prec(ch)) {
                post += st.top(); st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty()) {
        post += st.top(); st.pop();
    }
    return post;
}

// Build expression tree from postfix
Node* buildTree(const string& post) {
    stack<Node*> st;
    for (char ch : post) {
        if (isalnum(ch)) {
            st.push(new Node(ch));
        } else {
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            Node* temp = new Node(ch);
            temp->left = left;
            temp->right = right;
            st.push(temp);
        }
    }
    return st.top();
}

// Non-recursive postorder traversal
void postOrder(Node* root) {
    if (!root) return;
    stack<Node*> st;
    Node* last = nullptr;
    while (!st.empty() || root) {
        if (root) {
            st.push(root);
            root = root->left;
        } else {
            Node* curr = st.top();
            if (curr->right && last != curr->right) {
                root = curr->right;
            } else {
                cout << curr->val << " ";
                last = curr;
                st.pop();
            }
        }
    }
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    Node* root = buildTree(infixToPostfix(infix));

    cout << "Postorder traversal of the expression tree: ";
    postOrder(root);
    cout << endl;

    return 0;
}
