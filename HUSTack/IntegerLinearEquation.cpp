#include <iostream>
#include <vector>

using namespace std;

int countPartitions(int M, const vector<int>& a) {
    vector<int> dp(M + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < a.size(); ++i) {
        for (int j = a[i]; j <= M; ++j) {
            dp[j] += dp[j - a[i]];
        }
    }

    return dp[M];
}

int main() {
    int n, M;
    cin >> n >> M;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int result = countPartitions(M, a);
    cout << result << endl;

    return 0;
}
