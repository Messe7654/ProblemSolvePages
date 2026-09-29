#include <iostream>

int f[200'001][20];

int msb(int x) {
  return x & (~x + 1);
}

int nth(int x) {
  int count{0};
  for (int i{1}; i != x; i <<= 1, count++);
  return count;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int m; std::cin >> m;
  for (int i{1}; i <= m; i++) {
    std::cin >> f[i][0];
  }
  for (int s{1}; s <= 18; s++) {
    for (int i{1}; i <= m; i++) {
      f[i][s] = f[f[i][s - 1]][s - 1];
    }
  }
  int q; std::cin >> q;
  while (q-- != 0) {
    int n, x;
    std::cin >> n >> x;
    int ans{x};
    while (n) {
      ans = f[ans][nth(msb(n))];
      n = n & ~msb(n);
    }
    std::cout << ans << '\n';
  }
}