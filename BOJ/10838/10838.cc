#include <cassert>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_Stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, K; std::cin >> N >> K;

  std::vector<int> parent(N + 1);
  std::vector<int> color(N + 1);

  auto paint = [&](int a, int b, int c) {
    int da{0}; int db{0};
    
  };

  for (int i{0}; i < K; ++i) {
    int r; std::cin >> r;
    if (r == 1) {
      int a, b, c;
      std::cin >> a >> b >> c;

      continue;
    }
    if (r == 2) {
      int a, b;
      std::cin >> a >> b;

      continue;
    }
    if (r == 3) {
      int a, b;
      std::cin >> a >> b;

      continue;
    }
    assert(false && "r is not element of {1, 2, 3};");
  }
}