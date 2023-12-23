#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct SelectionInfo {
    int prevIndex;
    bool included;
};

int maxTotalDemand(vector<int>& demands, int n, int L1, int L2, vector<SelectionInfo>& selection) {
    vector<int> dp(n, 0);

    // Base case: when there is only one store
    dp[0] = demands[0];
    selection[0] = { -1, true }; // Mark the first store as selected

    int maxDemand = dp[0];
    int maxIndex = 0;

    for (int i = 1; i < n; ++i) {
        dp[i] = demands[i];
        selection[i] = { -1, true }; // Initialize with no previous index and include the current store

        for (int j = 0; j < i; ++j) {
            int distance = i - j;
            if (distance >= L1 && distance <= L2 && dp[i] < dp[j] + demands[i]) {
                dp[i] = dp[j] + demands[i];
                selection[i] = { j, true }; // Mark the current store as included and update previous index
            }
        }

        if (dp[i] > maxDemand) {
            maxDemand = dp[i];
            maxIndex = i;
        }
    }

    // Reconstruction of the selected dealers
    vector<int> selectedDealers;
    while (maxIndex != -1) {
        if (selection[maxIndex].included) {
            selectedDealers.push_back(maxIndex);
        }
        maxIndex = selection[maxIndex].prevIndex;
    }

    // Print the selected dealers (in reverse order as it was constructed backward)
    cout << "Selected Dealers: ";
    for (int i = selectedDealers.size() - 1; i >= 0; --i) {
        cout << selectedDealers[i] + 1 << " ";
    }
    cout << endl;

    return maxDemand;
}

int main() {
    int N, L1, L2;
    cin >> N >> L1 >> L2;

    vector<int> demands(N);
    for (int i = 0; i < N; ++i) {
        cin >> demands[i];
    }

    vector<SelectionInfo> selection(N);

    int result = maxTotalDemand(demands, N, L1, L2, selection);
    cout << "Maximum total demand for the product: " << result << endl;

    return 0;
}
