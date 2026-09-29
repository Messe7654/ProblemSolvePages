#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int V, E; std::cin >> V >> E;
  std::vector<std::vector<int>> graph(V + 1);

  for (int i{0}; i < E; ++i) {
    int A, B; std::cin >> A >> B;
    graph[A].push_back(B);
    graph[B].push_back(A);
  }

  std::vector<bool> visited(V + 1);
  std::vector<int> discover(V + 1);
  std::vector<int> low_link(V + 1);

  std::vector<std::pair<int, int>> answer;
  std::function<void(int, int)> dfs;
  dfs = [&, euler_count = (int)0](int now, int prev) mutable -> void {
    visited[now] = true;
    discover[now] = ++euler_count;
    low_link[now] = euler_count;

    for (const auto& next : graph[now]) {
      if (next == prev) continue;
      if (discover[next] == 0) {
        dfs(next, now);
        if (discover[now] < low_link[next]) {
          if (now < next) answer.emplace_back(now, next);
          else answer.emplace_back(next, now);
        }
        low_link[now] = std::min(low_link[now], low_link[next]);
      }
      else if (visited[next] == true) {
        low_link[now] = std::min(low_link[now], discover[next]);
      }
    }
  };

  for (int i{1}; i <= V; ++i) if (visited[i] == false) dfs(i, -1);

  std::sort(answer.begin(), answer.end());
  std::cout << answer.size() << '\n';
  for (const auto& [a, b] : answer) {
    std::cout << a << ' ' << b << '\n';
  }
}
