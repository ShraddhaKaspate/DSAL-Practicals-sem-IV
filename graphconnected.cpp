#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Node {
    string city;
    int time;
    Node* next;
    Node(string c, int t = 0) : city(c), time(t), next(nullptr) {}
};

class Graph {
    int adjMatrix[20][20], n;
    string cities[20];
    Node* head[20];

public:
    Graph() {
        for (int i = 0; i < 20; i++) head[i] = nullptr;
    }

    void createGraph();
    void createAdjList();
    void displayMatrix();
    void displayAdjList();
    void isConnected(); // <-- New function
private:
    void dfs(int v, vector<bool>& visited);
};

void Graph::createGraph() {
    cout << "\nEnter number of cities (max 20): ";
    cin >> n;

    cout << "Enter city names:\n";
    for (int i = 0; i < n; i++) cin >> cities[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char path;
            cout << "Is there a path from " << cities[i] << " to " << cities[j] << "? (y/n): ";
            cin >> path;
            if (path == 'y') {
                cout << "Enter time to reach " << cities[j] << " from " << cities[i] << ": ";
                cin >> adjMatrix[i][j];
            } else {
                adjMatrix[i][j] = 0;
            }
        }
    }
    createAdjList();
}

void Graph::createAdjList() {
    for (int i = 0; i < n; i++) {
        head[i] = new Node(cities[i]);
        Node* temp = head[i];
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != 0) {
                temp->next = new Node(cities[j], adjMatrix[i][j]);
                temp = temp->next;
            }
        }
    }
}

void Graph::displayMatrix() {
    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < n; i++) cout << cities[i] << "\t";
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << adjMatrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

void Graph::displayAdjList() {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        Node* temp = head[i];
        while (temp) {
            cout << temp->city;
            if (temp->time > 0) cout << " (" << temp->time << " min)";
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << "\n";
    }
}

// DFS utility
void Graph::dfs(int v, vector<bool>& visited) {
    visited[v] = true;
    for (int j = 0; j < n; j++) {
        if (adjMatrix[v][j] != 0 && !visited[j]) {
            dfs(j, visited);
        }
    }
}

// Check if graph is connected
void Graph::isConnected() {
    vector<bool> visited(n, false);
    dfs(0, visited); // start DFS from node 0

    bool connected = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            connected = false;
            break;
        }
    }

    if (connected)
        cout << "\nThe graph is CONNECTED.\n";
    else
        cout << "\nThe graph is NOT CONNECTED.\n";
}

int main() {
    Graph g;
    int choice;

    while (true) {
        cout << "\nMenu:";
        cout << "\n1. Enter Graph";
        cout << "\n2. Display Adjacency Matrix";
        cout << "\n3. Display Adjacency List";
        cout << "\n4. Check if Graph is Connected";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: g.createGraph(); break;
            case 2: g.displayMatrix(); break;
            case 3: g.displayAdjList(); break;
            case 4: g.isConnected(); break;
            case 5: exit(0);
            default: cout << "Invalid choice!\n";
        }
    }
}
