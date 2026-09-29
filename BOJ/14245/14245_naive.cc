#include <iostream>

int A[500'001];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n;
  std::cin >> n;

  for (int i{0}; i < n; ++i) {
    std::cin >> A[i];
  }

  int m;
  std::cin >> m;

  for (int i{0}; i < m; ++i) {
    int op;
    std::cin >> op;

    if (op == 1) {
      int a, b, c;
      std::cin >> a >> b >> c;
      for (int i{a}; i <= b; ++i) {
        A[i] ^= c;
      }
    }
    else {
      int a;
      std::cin >> a;
      std::cout << A[a] << '\n';
    }
  }
}