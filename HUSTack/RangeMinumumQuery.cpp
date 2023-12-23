#include <iostream>
#include <vector>
#include <cmath>
#define INT_MAX 1000000
using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int size) {
        n = 1 << int(ceil(log2(size))); // Get the next power of 2
        tree.resize(2 * n, INT_MAX);
    }

    void build(const vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            tree[n + i] = arr[i];
        }

        for (int i = n - 1; i > 0; i--) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    int query(int left, int right) {
        left += n;
        right += n;
        int min_val = INT_MAX;

        while (left <= right) {
            if (left % 2 == 1) {
                min_val = min(min_val, tree[left]);
                left++;
            }
            if (right % 2 == 0) {
                min_val = min(min_val, tree[right]);
                right--;
            }
            left /= 2;
            right /= 2;
        }

        return min_val;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int m;
    cin >> m;

    SegmentTree st(n);
    st.build(a);

    long long Q = 0;

    for (int k = 0; k < m; k++) {
        int i, j;
        cin >> i >> j;
        i--; // Convert to 0-based index
        j--;

        int min_val = st.query(i, j);
        Q += min_val;
    }

    cout << Q << endl;

    return 0;
}