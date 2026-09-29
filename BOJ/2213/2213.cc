#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  std::vector<int> weight(N);
  std::vector<std::vector<int>> adjacency_list(N);

  for (int& w : weight) std::cin >> w;
  for (int i{1}; i < N; ++i) {
    int a, b;
    std::cin >> a >> b;
    --a; --b;
    adjacency_list[a].push_back(b);
    adjacency_list[b].push_back(a);
  }

  
}