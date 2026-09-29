#include <iostream>

// g(1) = 0, g(2) = 1, g(3) = 2, ...

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  int g{0};
  for (int i{0}; i < N; i++) {
    int k; std::cin >> k;
    g ^= k;
  }

  std::cout << ((g & 1) ? "cubelover" : "koosaga");
}