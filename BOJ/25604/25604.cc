#include <iostream>
#include <vector>

struct info {
  int index;
  int d;
  int m;
  int r;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M, T;
  std::cin >> N >> M >> T;
  std::vector<info> informations(N);

  for (int i{0}; i < N; ++i) {
    int d, m, r;
    std::cin >> d >> m >> r;
    informations[i] = {i, d, m, r};
  }
}