#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include <set>

int BFS(const std::vector<std::vector<int>>& graph, int start) {
  int N = static_cast<int>(graph.size()) - 1;
  std::vector<bool> visited(N + 1);
  std::queue<std::pair<int, int>> queue;
  visited[start] = true;
  queue.push({start, 0});
  int max{0};
  while (queue.empty() != true) {
    auto [now, dist] = queue.front(); queue.pop();
    max = std::max(max, dist);
    for (const auto& next : graph[now]) {
      if (visited[next] == true) continue;
      visited[next] = true;
      queue.push({next, dist + 1});
    }
  }
  return max;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<std::vector<int>> graph(N + 1);
  int a, b;

  std::set<std::pair<int, int>> set;

  while (std::cin >> a >> b) {
    if (a == -1 && b == -1) break;
    graph[a].push_back(b);
    graph[b].push_back(a);
    if (a > b) std::swap(a, b);
    assert(set.insert({a, b}).second == true && "단순 그래프가 아님");
  }
  
  int min{0x7FFFFFFF};
  std::vector<int> ans;

  for (int i{1}; i <= N; ++i) {
    auto now_score = BFS(graph, i);
    if (now_score < min) {
      ans.clear();
      ans.push_back(i);
      min = now_score;
    }
    else if (now_score == min) {
      ans.push_back(i);
    }
  }

  std::cout << min << ' ' << ans.size() << '\n';
  for (std::size_t i{0}; i < ans.size(); ++i) {
    std::cout << ans[i] << ((i + 1 == ans.size()) ? '\n' : ' ');
  }
}