#include <functional>
#include <iostream>
#include <vector>
#include <queue>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int K; std::cin >> K;
  for (int testcase{1}; testcase <= K; ++testcase) {
    int V, E;
    std::cin >> V >> E;

    std::vector<std::vector<int>> graph(V + 1);
    for (int i{0}; i < E; ++i) {
      int a, b;
      std::cin >> a >> b;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }

    bool is_bipartite{true};
    std::vector<int> color(V + 1);
    std::vector<bool> visited(V + 1);
    std::function<void(int)> BFS;
    BFS = [&](int start) -> void {
      std::queue<int> queue;
      queue.push(start);
      visited[start] = true;
      color[start] = 1;
      
      while (queue.empty() != true) {
        auto now = queue.front(); queue.pop();
        auto now_color = color[now];

        for (const auto& next : graph[now]) {
          if (visited[next] != true) {
            visited[next] = true;
            color[next] = (now_color == 1) ? 2: 1;
            queue.push(next);
          }
          else if (color[next] == color[now]) {
            is_bipartite = false;
            return;
          }
        }
      }
    };

    for (int i{1}; i <= V; ++i) {
      if (is_bipartite && visited[i] != true) BFS(i);
    }

    std::cout << ((is_bipartite) ? "YES\n" : "NO\n");
  }
}