#include <algorithm>
#include <iostream>
#include <vector>

#define debug if (local) std::cout
#ifdef DEBUG
constexpr bool local = true;
#else
constexpr bool local = false;
#endif

std::pair<int, int> edges[2'000'001];

auto print = [](auto& list) -> void {
  int size = static_cast<int>(list.size());
  debug << "[";
  if (size == 0) debug << "]\n";
  for (int i{0}; i < size; i++) {
    debug << list[i] << ((i + 1 == size) ? "]\n" : ", ");
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;
  for (int i{1}; i <= M; i++) {
    int x, y;
    std::cin >> x >> y;
    edges[i] = {x, y};
  }

  std::sort(edges + 1, edges + M + 1);

  debug << "[";
  for (int i{1}; i <= M; i++) {
    debug << "(" << edges[i].first << ", " << edges[i].second << ")"
        << ((i == M) ? "]\n" : ", ");
  }

  

  for (int i{1}; i <= M; i++) {
    
  }
}