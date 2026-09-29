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

  std::vector<bool> comb(N);
  std::generate(comb.begin(), comb.begin() + M, []() { return true; });

  do {
    for (int i{0}; i < N; ++i) {
      if (comb[i] == true) std::cout << pool[i] << ' ';
    }
    std::cout << '\n';
  } while (std::prev_permutation(comb.begin(), comb.end()));
}