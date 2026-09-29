#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

constexpr int kMax = 100;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;
  std::vector<std::vector<int>> graph(N + 2);
  std::vector<std::vector<int>> capacity(N + 2, std::vector<int>(N + 2));
  std::vector<std::vector<int>> flow(N + 2, std::vector<int>(N + 2));

  for (int i{0}; i < M; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    graph[a].push_back(b);
    graph[b].push_back(a);
    capacity[a][b] = capacity[b][a] = c;
  }

  int source, sync;
  std::cin >> source >> sync;

  auto MaxFlow = [&]() -> long long {
    std::vector<int> parent(N + 2);
    long long ret{0};

    auto BFS = [&]() -> bool {
      std::fill(parent.begin(), parent.end(), -1);
      std::vector<bool> visited(N + 2);
      std::queue<int> queue;

      queue.push(source);
      visited[source] = true;

      while (queue.empty() != true) {
        auto now = queue.front();
        queue.pop();

        for (const auto& next : graph[now]) {
          if (visited[next] == true || capacity[now][next] - flow[now][next] <= 0) continue;
          visited[next] = true;
          queue.push(next);
          parent[next] = now;
          if (next == sync) return true;
        }
      }
      return false;
    };

    while (BFS()) {
      int now_flow = kMax;
      for (int i{sync}; i != source; i = parent[i]) {
        int p = parent[i];
        now_flow = std::min(now_flow, capacity[p][i] - flow[p][i]);
      }
      for (int i{sync}; i != source; i = parent[i]) {
        int p = parent[i];
        flow[p][i] += now_flow;
        flow[i][p] -= now_flow;
      }
      ret += now_flow;
    }
    return ret;
  };

  std::cout << MaxFlow();
}