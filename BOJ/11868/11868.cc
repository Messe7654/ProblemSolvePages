#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  int G{0};
  for (int i{0}; i < N; i++) {
    int P; std::cin >> P;
    G ^= P;
  }
  std::cout << ((G) ? "koosaga" : "cubelover");
}