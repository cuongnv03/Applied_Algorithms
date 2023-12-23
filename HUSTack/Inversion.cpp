#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

long long mergeAndCountInversions(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1);
    vector<int> R(n2);
    
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    long long inversions = 0;
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            inversions += (mid - left + 1 - i);
            inversions %= MOD;
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    return inversions;
}

long long mergeSortAndCountInversions(vector<int>& arr, int left, int right) {
    long long inversions = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inversions += mergeSortAndCountInversions(arr, left, mid);
        inversions %= MOD;
        inversions += mergeSortAndCountInversions(arr, mid + 1, right);
        inversions %= MOD;
        inversions += mergeAndCountInversions(arr, left, mid, right);
        inversions %= MOD;
    }
    return inversions;
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    long long inversions = mergeSortAndCountInversions(arr, 0, n - 1);
    cout << inversions << endl;

    return 0;
}
