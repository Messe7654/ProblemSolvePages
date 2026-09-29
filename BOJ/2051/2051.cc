#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;

  std::vector<std::vector<int>> graph(N + 1);
  for (int i{1}; i <= N; ++i) {
    int cnt; std::cin >> cnt;
    graph[i].resize(cnt);
    for (auto& j : graph[i]) std::cin >> j;
  }

  
}