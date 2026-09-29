#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M, K;
  std::cin >> N >> M >> K;

  int entire_candies{0};
  std::vector<int> candies(N + 1);
  for (int i{1}; i <= N; ++i) {
    std::cin >> candies[i];
    entire_candies += candies[i];
  }

  std::vector<std::vector<int>> graph(N + 1);
  for (int i{0}; i < M; ++i) {
    int a, b;
    std::cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  // graph의 각 connected component의 (|V_cc|, 캔디의 합)을 구함
  struct cc_info {
    int number_of_vertices;
    int sum_of_candies;
  };

  std::vector<cc_info> cc_infos;
  std::vector<bool> visited(N + 1);

  std::function<void(int)> dfs;
  dfs = [&](int now) -> void {
    std::vector<int> stack;
    stack.push_back(now);

    int number_of_vertices{0}, sum_of_candies{0};

    while (stack.empty() != true) {
      auto now = stack.back();
      stack.pop_back();

      if (visited[now] == true) continue;
      visited[now] = true;

      ++number_of_vertices;
      sum_of_candies += candies[now];

      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        stack.push_back(next);
      }
    }

    cc_infos.push_back({number_of_vertices, sum_of_candies});
  };

  for (int i{1}; i <= N; ++i) {
    if (visited[i] != true) dfs(i);
  }

  std::vector<int> DP(K);
  for (const auto& [V, S] : cc_infos) {
    for (int j{K - 1}; j - V >= 0; --j) {
      DP[j] = std::max(DP[j], DP[j - V] + S);
    }
  }
  std::cout << DP[K - 1];
}