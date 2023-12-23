#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int n, k;
vector<vector<int> > c;
vector<vector<int> > dp;

int tsp(int mask, int pos, vector<bitset<10> >& visited) {
    if (mask == (1 << (2 * n + 1)) - 1) {
        return c[pos][0];
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;
    for (int i = 1; i <= 2 * n; ++i) {
        if (!(mask & (1 << i))) {
            if (i > n && visited[pos][i - n] && (mask | (1 << i)) <= ((1 << (2 * n + 1)) - 1)) {
                ans = min(ans, c[pos][i] + tsp(mask | (1 << i), i, visited));
            } else if (i <= n) {
                if (visited[pos][i] < k) {
                    visited[pos][i]++;
                    ans = min(ans, c[pos][i] + tsp(mask | (1 << i), i, visited));
                    visited[pos][i]--;
                }
            }
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    cin >> n >> k;

    c.resize(2 * n + 1, vector<int>(2 * n + 1));
    dp.resize(1 << (2 * n + 1), vector<int>(2 * n + 1, -1));

    vector<bitset<10>> visited(2 * n + 1);

    for (int i = 0; i <= 2 * n; ++i) {
        for (int j = 0; j <= 2 * n; ++j) {
            cin >> c[i][j];
        }
    }

    visited[0][0] = 1;
    int shortestRoute = tsp(1, 0, visited);
    cout << shortestRoute << endl;

    return 0;
}
