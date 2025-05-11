#include<iostream>
using namespace std;

class Tree {
    int a[20][20], v, e;
    bool visited[20];

public:
    void input();
    void display();
    void minimum();
};

void Tree::input() {
    cout << "Enter number of branches: ";
    cin >> v;

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        for (int j = 0; j < v; j++) {
            a[i][j] = 999; // 999 means no direct connection
        }
    }

    cout << "Enter number of connections: ";
    cin >> e;

    for (int i = 0; i < e; i++) {
        int u, w, l;
        cout << "\nEnter the two branches (start and end): ";
        cin >> l >> u;
        cout << "Enter the charge between branch " << l << " and " << u << ": ";
        cin >> w;
        a[l-1][u-1] = a[u-1][l-1] = w;
    }
}

void Tree::display() {
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (a[i][j] == 999)
                cout << "INF\t";
            else
                cout << a[i][j] << "\t";
        }
        cout << "\n";
    }
}

void Tree::minimum() {
    int totalCost = 0;
    visited[0] = true; // Start from first branch

    cout << "\nMinimum Cost Connections (Prim's Algorithm):\n";
    for (int edges = 0; edges < v - 1; edges++) {
        int min = 999, u = -1, vtx = -1;
        for (int i = 0; i < v; i++) {
            if (visited[i]) {
                for (int j = 0; j < v; j++) {
                    if (!visited[j] && a[i][j] < min) {
                        min = a[i][j];
                        u = i;
                        vtx = j;
                    }
                }
            }
        }

        if (u != -1 && vtx != -1) {
            cout << "Connection: " << (u + 1) << " -> " << (vtx + 1) << " with cost " << min << "\n";
            visited[vtx] = true;
            totalCost += min;
        }
    }

    cout << "\nTotal Minimum Cost: " << totalCost << "\n";
}

int main() {
    Tree t;
    int choice;

    do {
        cout << "\n====== Prim's Algorithm Menu ======\n";
        cout << "1. Input Graph\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Find Minimum Cost Connections\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: t.input(); break;
            case 2: t.display(); break;
            case 3: t.minimum(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
