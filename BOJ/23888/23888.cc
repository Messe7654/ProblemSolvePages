#include <iostream>

long long GCD(long long a, long long b) {
  if (a < b) std::swap(a, b);
  while (b > 0) {
    long long r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  long long a, d;
  std::cin >> a >> d;

  auto Query01 = [&](int l, int r) -> long long {
    return 1LL * (r - l + 1) * a + 1LL * (r - l + 1) * (l + r - 2) / 2 * d;
  };

  auto Query02 = [&](int l, int r) -> long long {
    if (l == r) return a + d * (l - 1);
    return GCD(a, d);
  };

  int q;
  std::cin >> q;

  for (int i{0}; i < q; ++i) {
    int op, l, r;
    std::cin >> op >> l >> r;
    if (1 == op) std::cout << Query01(l, r) << '\n';
    else if (2 == op) std::cout << Query02(l, r) << '\n';
    // else assert(false);
  }
}