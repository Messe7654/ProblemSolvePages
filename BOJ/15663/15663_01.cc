#include <algorithm>
#include <iostream>
#include <vector>

template <typename FIt>
void println(FIt first, FIt last) {
  while (first != last) {
    std::cout << *first++ << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  std::vector<int> pool(N);
  for (int& i : pool) std::cin >> i;
  std::sort(pool.begin(), pool.end());

  do {
    if (std::is_sorted(pool.begin() + M, pool.end())) println(pool.begin(), pool.begin() + M);
  } while (std::next_permutation(pool.begin(), pool.end()));
}