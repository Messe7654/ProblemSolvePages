#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

int solve(const std::vector<std::vector<int>>& graph) {
  std::size_t n = graph.size();
  std::vector<int> group(n);

  auto BFS = [&, idx = 0](int start) mutable -> bool {
    if (group[start] != 0) return false;
    ++idx;
    
    bool is_tree{true};
    std::vector<bool> visited(n);
    visited[start] = true;
    std::queue<std::pair<int, int>> queue; // {prev, curr}
    queue.push({-1, start});

    std::vector<int> connected_component;

    while (queue.empty() != true) {
      auto [prev, curr] = queue.front(); queue.pop();

      connected_component.push_back(curr);

      for (const auto& next : graph[curr]) {
        if (prev == next) continue;  // tree edge
        if (visited[next] == true) { // cycle
          is_tree = false; continue;
        }

        visited[next] = true;
        group[next] = idx;
        queue.push({curr, next});
      }
    }

    return is_tree;
  };

  int ret{0};
  for (std::size_t i{0}; i < n; ++i) {
    if (BFS(i)) ++ret;
  }
  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int testcase{1};
  int n, m;
  while (std::cin >> n >> m) {
    if (n == 0 && m == 0) break;

    std::vector<std::vector<int>> graph(n);
    for (int i{0}; i < m; ++i) {
      int a, b; std::cin >> a >> b;
      --a, --b;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }

    int count = solve(graph);

    std::cout << "Case " << testcase++ << ": ";
    if (count == 0) std::cout << "No trees.\n";
    else if (count == 1) std::cout << "There is one tree.\n";
    else std::cout << "A forest of " << count << " trees.\n";
  }
}