#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int N, M;
  std::cin >> N >> M;

  std::vector<bool> comb(N);
  std::generate(comb.begin(), comb.begin() + M, []() { return true; });
  do {
    for (int i{0}; i < N; ++i)
      if (comb[i] == true) std::cout << i + 1 << ' ';
    std::cout << '\n';
  } while (std::prev_permutation(comb.begin(), comb.end()));
}