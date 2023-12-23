#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isSafe(const vector<vector<int> >& teacherPrefs, vector<int>& assignedCourses, int course, int teacher, const vector<pair<int, int> >& conflicts) {
    // Check if the course is in the teacher's preference list and hasn't been assigned to any other teacher
    return (find(teacherPrefs[teacher].begin(), teacherPrefs[teacher].end(), course) != teacherPrefs[teacher].end()) &&
           (find(assignedCourses.begin(), assignedCourses.end(), course) == assignedCourses.end()) &&
           all_of(conflicts.begin(), conflicts.end(), [&](pair<int, int> conflict) {
               return !(assignedCourses[conflict.first - 1] == course && assignedCourses[conflict.second - 1] == course);
           });
}

bool canAssignCourse(const vector<vector<int> >& teacherPrefs, vector<int>& assignedCourses, int courseIndex, int m, const vector<pair<int, int> >& conflicts) {
    if (courseIndex == assignedCourses.size()) {
        return true;
    }

    for (int i = 0; i < m; ++i) {
        if (isSafe(teacherPrefs, assignedCourses, courseIndex + 1, i, conflicts)) {
            assignedCourses[courseIndex] = i + 1;
            if (canAssignCourse(teacherPrefs, assignedCourses, courseIndex + 1, m, conflicts)) {
                return true;
            }
            assignedCourses[courseIndex] = -1;
        }
    }
    return false;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int> > teacherPrefs(m, vector<int>());
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int course;
            cin >> course;
            teacherPrefs[i].push_back(course);
        }
    }

    int k;
    cin >> k;
    vector<pair<int, int> > conflicts(k);
    for (int i = 0; i < k; ++i) {
        cin >> conflicts[i].first >> conflicts[i].second;
    }

    vector<int> assignedCourses(n, -1);

    int maxLoad = 0;
    if (canAssignCourse(teacherPrefs, assignedCourses, 0, m, conflicts)) {
        maxLoad = *max_element(assignedCourses.begin(), assignedCourses.end());
    } else {
        maxLoad = -1;
    }

    // Increment the maxLoad by 1 for correct output if a solution exists
    if (maxLoad != -1) {
        maxLoad += 1;
    }

    cout << maxLoad << endl;

    return 0;
}
