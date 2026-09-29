#include <iostream>

int main() {
  int N, M; std::cin >> N >> M;
  if (N != M) std::cout << (std::min(N, M) - 1) * (std::min(N, M) - 1) << '\n';
  else {
    int l = N - 1;
    int max{0};
    for (int i{1}; i < l; ++i) {
      max = std::max(i * i + (l - i) * (l - i), max);
    }

    std::cout << max << '\n';
  }
}