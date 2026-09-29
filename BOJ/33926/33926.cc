#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  long long N, M; std::cin >> N >> M;

  auto score = std::vector(N, std::vector<long long>(M));
  auto color = std::vector(N, std::vector<long long>(M));
  auto DP = std::vector(N, std::vector<std::pair<long long, long long>>(M));

  for (long long row{0}; row < N; ++row) {
    for (long long col{0}; col < M; ++col) {
      std::cin >> score[row][col];
    }
  }

  for (long long row{0}; row < N; ++row) {
    for (long long col{0}; col < M; ++col) {
      std::cin >> color[row][col];
    }
  }

  DP[0][0] = {score[0][0], score[0][0]};

  for (long long row{1}; row < N; ++row)
    DP[row][0] = {
      (DP[row - 1][0].first + score[row][0]) * (1 - (color[row][0] << 1)), 
      (DP[row - 1][0].first + score[row][0]) * (1 - (color[row][0] << 1))
    };

  for (long long col{1}; col < M; ++col)
    DP[0][col] = {
      (DP[0][col - 1].first + score[0][col]) * (1 - (color[0][col] << 1)), 
      (DP[0][col - 1].first + score[0][col]) * (1 - (color[0][col] << 1))
    };

  for (long long row{1}; row < N; ++row) {
    for (long long col{1}; col < M; ++col) {
      long long sign = 1 - (color[row][col] << 1);
      DP[row][col] = std::minmax({
        (DP[row][col - 1].first + score[row][col]) * sign,
        (DP[row][col - 1].second + score[row][col]) * sign,
        (DP[row - 1][col].first + score[row][col]) * sign,
        (DP[row - 1][col].second + score[row][col]) * sign
      });
    }
  }

  std::cout << DP[N - 1][M - 1].second << '\n';
}