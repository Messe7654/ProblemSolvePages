#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n, m; std::cin >> n >> m;
  std::vector<int> parent(n + 1);
  std::vector<std::vector<int>> children(n + 1);
  std::cin >> parent[1];
  for (int i{2}; i <= n; ++i) {
    std::cin >> parent[i];
    children[parent[i]].push_back(i);
  }

  std::vector<int> discover(n + 1);
  std::vector<int> finished(n + 1);

  std::function<void(int)> DFS;
  DFS = [&, order = (int)0](int now) mutable -> void {
    discover[now] = ++order;
    for (const auto& next : children[now]) {
      DFS(next);
    }   
    finished[now] = order;
  };

  DFS(1);

  std::vector<int> acc(n + 2);
  for (int i{0}; i < m; ++i) {
    int a, b; std::cin >> a >> b;
    acc[discover[a]] += b;
    acc[finished[a] + 1] -=b;
  }

  for (int i{1}; i <= n; ++i) acc[i] += acc[i - 1];

  for (int i{1}; i <= n; ++i) {
    std::cout << acc[discover[i]] << ((i == n) ? '\n' : ' ' );
  }
}