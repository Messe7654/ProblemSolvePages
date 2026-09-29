#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

constexpr int kInf = 0x7FFFFFFF;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int V, E; std::cin >> V >> E;
  int K; std::cin >> K; --K;

  std::vector<std::vector<std::pair<int, int>>> G(V);
  
  for (int i{1}; i <= E; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u; --v;

    G[u].emplace_back(v, w);
  }

  std::vector<bool> visited(V);
  std::vector<int> distance(V, kInf);
  distance[K] = 0;

  std::priority_queue<
    std::pair<int, int>,
    std::vector<std::pair<int, int>>,
    std::greater<>> pq;

  pq.push({0, K});

  while (pq.empty() != true) {
    auto [curr_weight, curr_idx] = pq.top(); pq.pop();

    if (visited[curr_idx]) continue;
    visited[curr_idx] = true;

    for (const auto& [next_idx, next_weight] : G[curr_idx]) {
      if (visited[next_idx] || distance[curr_idx] + next_weight >= distance[next_idx]) continue;
      distance[next_idx] = distance[curr_idx] + next_weight;
      pq.emplace(distance[next_idx], next_idx);
    }
  }

  for (int i{0}; i < V; ++i) {
    if (distance[i] == kInf) std::cout << "INF\n";
    else std::cout << distance[i] << '\n';
  }
}