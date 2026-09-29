#include <iostream>
#include <vector>

constexpr int kMod = 1'000'000'007;

int main() {
  // 0 0 0 
  // 1 1 1 
  // 2 2 2 
  // 5 5 5 
  // 7 7 7
  // * 10 + ?
  int N, M, K;
  std::cin >> N >> M >> K;
  std::vector<int> numbers(N);
  for (auto& number : numbers) std::cin >> number;
  auto DP = std::vector(M, std::vector<int>(K));

  // Round 1
  for (const auto number : numbers) {
    if (number == 0) continue;
    ++DP[0][number % K];
  }

  for (int round{2}; round <= M; ++round) {
    for (const auto number : numbers) {
      for (int i{0}; i < K; ++i) {
        DP[round - 1][(i * 10 + number) % K] += DP[round - 2][i];
        DP[round - 1][(i * 10 + number) % K] %= kMod;
      }
    }
  }
  std::cout << DP[M - 1][0] << '\n';
}