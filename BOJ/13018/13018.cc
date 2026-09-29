#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int GCD(int a, int b) {
  if (a < b) std::swap(a, b);
  while (b > 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main() {
  int n; std::cin >> n;

  std::vector<int> perm(n);
  std::generate(perm.begin(), perm.end(), [i = (int)0]() mutable { return ++i; });
  do {
    int k = std::accumulate(perm.begin(), perm.end(), 0, 
      [i = (int)0](int T, const auto& x) mutable {
       return T + (GCD(++i, x) > 1);
    });

    std::for_each(perm.begin(), perm.end(), [](auto& x) { std::cout << x << ' '; });
    std::cout << "k : " << k << '\n';
  } while (std::next_permutation(perm.begin(), perm.end()));
}