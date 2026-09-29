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

  std::vector<int> perm(N);
  std::generate(perm.begin(), perm.end(), [i = (int)0]() mutable { return ++i; });
  do {
    if (std::is_sorted(perm.begin() + M, perm.end())) println(perm.begin(), perm.begin() + M);
  } while (std::next_permutation(perm.begin(), perm.end()));
}