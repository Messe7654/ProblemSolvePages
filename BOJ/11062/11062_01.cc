#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    int N; std::cin >> N;
    std::vector<int> cards(N);
    std::vector<int> prefix_sum(N + 1);

    for (int i{0}; i < N; ++i) {
      std::cin >> cards[i];
      prefix_sum[i + 1] = prefix_sum[i] + cards[i];
    }

    auto solve = [&]() -> int {
      auto DP = std::vector(N + 1, std::vector<int>(N + 1));
      auto __imple__ = [&](auto&& self, int lhs, int rhs) -> int {
        int diff = rhs - lhs;
        if (diff <= 0) return 0;
        if (DP[lhs][rhs]) return DP[lhs][rhs];
        if (diff == 1) return DP[lhs][rhs] = cards[lhs];

        int select_lhs = (prefix_sum[rhs] - prefix_sum[lhs]) - self(self, lhs + 1, rhs);
        int select_rhs = (prefix_sum[rhs] - prefix_sum[lhs]) - self(self, lhs, rhs - 1);
        return DP[lhs][rhs] = std::max(select_lhs, select_rhs);
      };
      return __imple__(__imple__, 0, N);
    };

    std::cout << solve() << '\n';
  }
}