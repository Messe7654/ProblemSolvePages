#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<int> numbers(N << 1 | 1);
  std::vector<int> P(N << 1 | 1);

  for (int i{0}; i < N; ++i) {
    std::cin >> numbers[i << 1 | 1];
  }

  int c{0}, r{0};
  N = (N << 1 | 1);
  for (int i{0}; i < N; ++i) {
    int antipode = (c << 1) - i;
    if (i < r) {
      P[i] = std::min(r - i, P[antipode]);
    }

    while (i + P[i] + 1 < N && i - P[i] - 1 >= 0 &&
           numbers[i + P[i] + 1] == numbers[i - P[i] - 1])
      ++P[i];
  }

  for (int i : P) std::cout << i << ' ';
  std::cout << '\n';

  int M; std::cin >> M;
  for (int query_idx{1}; query_idx <= M; ++query_idx) {
    int S, E;
    std::cin >> S >> E;
    --S; --E;
    int mid = ((S << 1 | 1) + (E << 1 | 1)) >> 1;
    int len = (E - S + 1);
    std::cout << ((P[mid] >= len) ? "1\n" : "0\n");
  }
}