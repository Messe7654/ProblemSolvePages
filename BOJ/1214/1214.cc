#include <cmath>
#include <iostream>
#include <tuple>

std::tuple<int, int, int> EXGCD(int a, int b) {
  if (b == 0) return {a, 1, 0};
  auto [g, x, y] = EXGCD(b, a % b);
  return {g, y, x - (a / b) * y};
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int D, P, Q;
  std::cin >> D >> P >> Q;
  if (P < Q) std::swap(P, Q);
  int min = 0x7FFFFFFF;
  for (int i{0}; i <= Q - 1 && i <= (D - 1) / P + 1; ++i) {
    if ((int)std::ceil((double)(D - (P * i)) / Q) < 0) continue;
    min = std::min(P * i + (int)std::ceil((double)(D - (P * i)) / Q) * Q, min);
  } 

  std::cout << min;
}