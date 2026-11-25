#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main() {
  std::cin.tie(0)->sync_with_stdio(0);

  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    int N, W;
    std::cin >> N >> W;

    auto enemy = std::vector(2, std::vector<int>(N));
    for (auto& row : enemy)
      for (auto& curr_col : row)
        std::cin >> curr_col;

    const int kInf{N << 1 | 1};
    auto DP = std::vector(N + 1, std::array<int, 4>{});
    auto reset = [kInf](std::array<int, 4>& states) {
      for (int& state : states) state = kInf;
    };
    int ans{kInf};

    for (int start{0}; start < 4; ++start) {
      reset(DP[0]);
      DP[0][start] = 0;

      for (int i{1}; i <= N; ++i) {
        const int curr_col{i - 1};
        const int next_col{i % N};
        int H{0};

        for (int row{0}; row < 2; ++row) {
          if (enemy[row][curr_col] + enemy[row][next_col] <= W)
            H |= 1 << row;
        }
        const bool V = (enemy[0][curr_col] + enemy[1][curr_col] <= W);

        reset(DP[i]);
        for (int prev{0}; prev < 4; ++prev) {
          if (DP[i - 1][prev] == kInf) continue;

          for (int next{0}; next < 4; ++next) {
            if ((prev & next) || (next & H) != next) continue;

            const int remain = 3 ^ (prev | next);
            const int cost   = __builtin_popcount(next) + __builtin_popcount(remain) - (int)(remain == 3 && V);
            DP[i][next] = std::min(DP[i][next], DP[i - 1][prev] + cost);
          }
        }
      }

      ans = std::min(ans, DP[N][start]);
    }

    std::cout << ans << '\n';
  }
}
