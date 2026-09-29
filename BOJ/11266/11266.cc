#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int V, E; std::cin >> V >> E;
  std::vector<std::vector<int>> graph(V + 1);

  for (int i{0}; i < E; ++i) {
    int a, b; std::cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  std::vector<bool> visited(V + 1);
  std::vector<int> discover(V + 1);
  std::vector<int> low_link(V + 1);
  std::set<int> answer;

  std::function<void(int, int)> dfs;
  dfs = [&, euler_count = (int)0](int now, int prev) mutable -> void {
    visited[now] = true;
    discover[now] = ++euler_count;
    low_link[now] = euler_count;

    int dfs_childs_count{0};

    for (const auto& next : graph[now]) {
      if (next == prev) continue;
      if (discover[next] == 0) {
        ++dfs_childs_count;
        dfs(next, now);
        if (prev == -1 && dfs_childs_count >= 2) answer.insert(now);
        else if (prev != -1 && low_link[next] >= discover[now]) answer.insert(now);
        low_link[now] = std::min(low_link[now], low_link[next]);
      }
      else if (visited[next] == true) {
        low_link[now] = std::min(low_link[now], discover[next]);
      }
    }
  };

  for (int i{1}; i <= V; ++i) {
    if (discover[i] == 0) dfs(i, -1);
  }

  auto println = [](const auto& list) {
    if (list.empty()) { std::cout << '\n'; return; }
    int size = static_cast<int>(list.size());
    for (int i{0}; i < size; ++i) {
      std::cout << list[i] << ((i + 1 == size) ? '\n' : ' ');
    }
  };

  std::cout << answer.size() << '\n';
  for (const auto& i : answer) {
    std::cout << i << ' ';
  }
}