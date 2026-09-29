#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;
  std::vector<int> pool(N);
  for (int& i : pool) std::cin >> i;
  std::sort(pool.begin(), pool.end());

  std::vector<int> indices(N);
  std::generate(indices.begin(), indices.end(), [i = (int)-1]() mutable {
    return ++i;
  });

  std::vector<int> cycle(M);
  for (int i{0}; i < M; ++i) cycle[i] = N - i;

  do {
    for (int i{0}; i < M; ++i) {
      std::cout << pool[indices[i]] << ((i + 1 == M) ? '\n' : ' ');
    }
    bool terminal{true};
    for (int i{M - 1}; i >= 0; --i) {
      if (--cycle[i] == 0) {
        std::rotate(indices.begin() + i, indices.begin() + i + 1, indices.end());
        cycle[i] = N - i;
      }
      else {
        int j = cycle[i];
        std::swap(indices[i], indices[N - j]);
        terminal = false;
        break;
      }
    }
    if (terminal) break;
  } while (true);
}