#include <iostream>
#define MAX 100
#define INF 999999

using namespace std;

int main() {
    int n, i, j, k, r, l;
    float p[MAX];            // Probabilities
    float e[MAX][MAX];       // Expected cost
    float w[MAX][MAX];       // Sum of probabilities
    int root[MAX][MAX];      // Root table

    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter the probabilities:\n";
    for (i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    // Initialization
    for (i = 1; i <= n + 1; i++) {
        e[i][i - 1] = 0;
        w[i][i - 1] = 0;
    }

    // Building the e and w tables
    for (l = 1; l <= n; l++) { // l is the length of the subtree
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            e[i][j] = INF;
            w[i][j] = w[i][j - 1] + p[j];

            for (r = i; r <= j; r++) {
                float cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "\nMinimum cost of Optimal BST: " << e[1][n] << endl;

    return 0;
}
