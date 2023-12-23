#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int start, end;
};

bool compareSegments(const Segment &a, const Segment &b) {
    return a.end < b.end;
}

int largestNonOverlappingSubset(vector<Segment> &segments) {
    sort(segments.begin(), segments.end(), compareSegments);

    int count = 1;
    int lastEnd = segments[0].end;

    for (size_t i = 1; i < segments.size(); ++i) {
        if (segments[i].start > lastEnd) {
            count++;
            lastEnd = segments[i].end;
        }
    }

    return count;
}

int main() {
    int n;
    cin >> n;

    vector<Segment> segments(n);
    for (int i = 0; i < n; ++i) {
        cin >> segments[i].start >> segments[i].end;
    }

    int result = largestNonOverlappingSubset(segments);
    cout << result << endl;

    return 0;
}
