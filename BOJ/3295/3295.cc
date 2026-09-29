#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T;
  std::cin >> T;

  for (int testcase{1}; testcase <= T; ++testcase) {
    int n, m;
    std::cin >> n >> m;
    const int& bias = n;

    std::vector<std::vector<int>> graph(n);

    for (int i{0}; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      graph[u].push_back(v);
    }

    auto solve = [&]() -> int {
      std::vector<bool> visited(n);
      auto Clear = [&]() { std::fill(visited.begin(), visited.end(), false); };
      std::vector<int> left(n, -1), right(n, -1);
      std::function<bool(int)> DFS;
      DFS = [&](int now) -> bool {
        visited[now] = true;
        for (const auto& next : graph[now]) {
          if (left[next] == -1 || (!visited[left[next]] && DFS(left[next]))) {
            left[next] = now;
            right[now] = next;
            return true;
          }
        }
        return false;
      };

      int match{0};
      for (int i{0}; i < n; ++i) {
        Clear();
        if (DFS(i)) ++match;
      }
      return match;
    };

    std::cout << solve() << '\n';
  }
}
