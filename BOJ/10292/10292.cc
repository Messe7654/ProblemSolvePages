#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <set>

bool solve(int N, int M, const std::vector<std::vector<int>>& G) {
  std::vector<bool> visited(N + 1);
  std::vector<int> discover(N + 1);
  std::vector<int> low_link(N + 1);
  std::set<int> cut_vertices;
  std::function<void(int, int)> dfs;
  dfs = [&, euler_count = (int)0](int prev, int now) mutable -> void {
    visited[now] = true;
    discover[now] = ++euler_count;
    low_link[now] = euler_count;

    int dfs_child_count{0};
    for (const auto& next : G[now]) {
      if (prev == next) continue;
      if (discover[next] == 0) {
        dfs(now, next);
        ++dfs_child_count;
        if (prev != -1 && low_link[next] >= discover[now]) cut_vertices.insert(now);
        low_link[now] = std::min(low_link[now], low_link[next]);
      }
      else if (visited[next] == true)
        low_link[now] = std::min(low_link[now], discover[next]);
    }

    if (prev == -1 && dfs_child_count >= 2) cut_vertices.insert(now);
  };

  for (int i{1}; i <= N; ++i) {
    if (visited[i] == false) dfs(-1, i);
  }

  return !cut_vertices.empty();
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    int N, M; std::cin >> N >> M;
    std::vector<std::vector<int>> graph(N + 1);

    for (int i{0}; i < M; ++i) {
      int A, B; std::cin >> A >> B;
      graph[A].push_back(B);
      graph[B].push_back(A);
    }

    std::cout << ((solve(N, M, graph)) ? "YES\n" : "NO\n");
  }
}