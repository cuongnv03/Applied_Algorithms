#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canPlaceCows(const vector<int>& positions, int distance, int cows) {
    int lastPos = positions[0];
    int count = 1;

    for (size_t i = 1; i < positions.size(); ++i) {
        if (positions[i] - lastPos >= distance) {
            lastPos = positions[i];
            count++;
            if (count == cows)
                return true;
        }
    }
    return false;
}

int largestMinimumDistance(const vector<int>& positions, int cows) {
    int low = 1; // Minimum possible distance between cows
    int high = positions.back() - positions.front(); // Maximum possible distance between cows
    int result = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canPlaceCows(positions, mid, cows)) {
            result = max(result, mid);
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, C;
        cin >> N >> C;

        vector<int> positions(N);
        for (int i = 0; i < N; ++i) {
            cin >> positions[i];
        }

        sort(positions.begin(), positions.end());

        int maxDistance = largestMinimumDistance(positions, C);
        cout << maxDistance << endl;
    }

    return 0;
}
