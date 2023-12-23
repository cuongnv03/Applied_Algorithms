#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 999
#define MAX_M 999

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y, steps;
} Point;

Point create_point(int x, int y, int steps) {
    Point p;
    p.x = x;
    p.y = y;
    p.steps = steps;
    return p;
}

bool is_valid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int find_shortest_path(int n, int m, int r, int c, int maze[MAX_N][MAX_M]) {
    bool visited[MAX_N][MAX_M] = {false};
    Point queue[MAX_N * MAX_M];
    int front = 0, rear = 0;

    queue[rear++] = create_point(r, c, 0);
    visited[r][c] = true;

    while (front < rear) {
        Point current = queue[front++];
        int x = current.x;
        int y = current.y;
        int steps = current.steps;

        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            return steps + 1; // We have reached an exit cell
        }

        for (int i = 0; i < 4; i++) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];

            if (is_valid(new_x, new_y, n, m) && !visited[new_x][new_y] && maze[new_x][new_y] == 0) {
                queue[rear++] = create_point(new_x, new_y, steps + 1);
                visited[new_x][new_y] = true;
            }
        }
    }

    return -1; // No path to exit was found
}

int main() {
    int n, m, r, c;
    scanf("%d %d %d %d", &n, &m, &r, &c);

    int maze[MAX_N][MAX_M];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    int result = find_shortest_path(n, m, r - 1, c - 1, maze);
    printf("%d\n", result);

    return 0;
}

