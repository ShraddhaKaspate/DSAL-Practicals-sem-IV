#include <iostream>
using namespace std;

class OBST {
    int a[10], r[10][10], n;
    float p[10], q[10], w[10][10], c[10][10];

public:
    void accept();
    void construct();
    int find_min(int, int);
    void display_tree(int, int);
};

void OBST::accept() {
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements (keys): ";
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    cout << "Enter " << n << " successful search probabilities: ";
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    cout << "Enter " << n + 1 << " unsuccessful search probabilities: ";
    for (int i = 0; i <= n; i++)
        cin >> q[i];
}

void OBST::construct() {
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;

        if (i < n) {
            w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }
    }

    for (int m = 2; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            int k = find_min(i, j);
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }

    cout << "\nRoot of OBST: " << a[r[0][n]] << "\n";
    cout << "Left subtree of " << a[r[0][n]] << ": ";
    display_tree(0, r[0][n] - 1);
    cout << "Right subtree of " << a[r[0][n]] << ": ";
    display_tree(r[0][n], n);
}

int OBST::find_min(int i, int j) {
    int minIndex = -1;
    float minValue = 1e9; // A large value

    for (int k = r[i][j - 1]; k <= r[i + 1][j]; k++) {
        float cost = c[i][k - 1] + c[k][j];
        if (cost < minValue) {
            minValue = cost;
            minIndex = k;
        }
    }

    return minIndex;
}

void OBST::display_tree(int i, int j) {
    if (r[i][j] == 0) {
        cout << "NULL\n";
        return;
    }

    cout << a[r[i][j]] << "\n";
    cout << "Left subtree of " << a[r[i][j]] << ": ";
    display_tree(i, r[i][j] - 1);
    cout << "Right subtree of " << a[r[i][j]] << ": ";
    display_tree(r[i][j], j);
}

int main() {
    OBST tree;
    tree.accept();
    tree.construct();
    return 0;
}

3
10 20 30 
0.3 0.2 0.1
0.3 0.3 0.3 0.3 
