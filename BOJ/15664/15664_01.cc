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

  std::vector<bool> comb(N);
  std::generate(comb.begin(), comb.begin() + M, []() { return true; });

  std::vector<std::vector<int>> res;
  do {
    std::vector<int> now;
    for (int i{0}; i < N; ++i) if (comb[i]) now.push_back(pool[i]);
    res.push_back(now);
  } while (std::prev_permutation(comb.begin(), comb.end()));

  std::sort(res.begin(), res.end());
  res.erase(std::unique(res.begin(), res.end()), res.end());

  for (const auto& v : res) {
    println(v.begin(), v.end());
  }
}