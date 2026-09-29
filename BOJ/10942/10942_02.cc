#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<int> numbers(N);
  for (int i{0}; i < N; ++i) std::cin >> numbers[i];

  auto DP = std::vector(N, std::vector<int>(N));

  for (int i{0}; i < N; ++i) {
    // 홀수 길이
    for (int left{i}, right{i}; left >= 0 && right < N; --left, ++right) {
      if (numbers[left] == numbers[right]) DP[left][right] = 1;
      else break;
    }

    // 짝수 길이
    for (int left{i}, right{i + 1}; left >= 0 && right < N; --left, ++right) {
      if (numbers[left] == numbers[right]) DP[left][right] = 1;
      else break;
    }
  }

  int M; std::cin >> M;
  for (int query_idx{1}; query_idx <= M; ++query_idx) {
    int S, E;
    std::cin >> S >> E;
    std::cout << DP[--S][--E] << '\n';
  }
}