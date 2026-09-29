#include <iostream>
#include <vector>

std::vector<int> adj[5'001];
int DP[5'001];
int height[5'001];

int dfs(int start) {
  int max{0};
  for (auto next : adj[start]) {
    max = std::max((DP[next] != 0) ? DP[next] : dfs(next), max);
  }
  return DP[start] = max + 1;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  for (int i{1}; i <= N; i++) {
    std::cin >> height[i];
  }

  for (int i{0}; i < M; i++) {
    int a, b;
    std::cin >> a >> b;
    if (height[a] > height[b]) std::swap(a, b);
    adj[a].push_back(b);
  }

  for (int i{1}; i <= N; i++) {
    std::cout << ((DP[i] != 0) ? DP[i] : dfs(i)) << '\n';
  }
}