#include <cstdio>
#include <cstring>

struct shark { int a, b, c; };
const int N = 55;
shark arr[N];
int B[N];
bool visited[N];
int n;

bool operator==(const shark &a, const shark &b) {
    if (a.a == b.a && a.b == b.b && a.c == b.c) return true;
    return false;
}

bool operator>(const shark &a, const shark &b) {
    if (a.a < b.a || a.b < b.b || a.c < b.c) return true;
    return false;
}

bool dfs(int a) {
    visited[a] = true;
    for (int i = 0; i < n; i++) {
        if (arr[a] == arr[i] && a < i) continue;
        if (i == a || arr[a] > arr[i]) continue;
        if (B[i] == -1 || !visited[B[i]] && dfs(B[i])) {
            B[i] = a;
            return true;
        }
    }
    return false;
}

int main() {
     scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, b, c; scanf("%d %d %d", &a, &b, &c);
        arr[i] = {a, b, c};
    }
    memset(B, -1, sizeof B);
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            memset(visited, false, sizeof visited);
            if (dfs(i)) ret++;
        }
    }
    printf("%d", n - ret);
}