#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;

  for (int testcase{1}; testcase <= T; ++testcase) {
    int K; std::cin >> K;
    std::vector<std::vector<int>> DP(K + 1, std::vector<int>(K + 1));
    std::vector<int> sum(K + 1);
    for (int i{1}; i <= K; ++i) {
      std::cin >> DP[i][i];
      sum[i] = sum[i - 1] + DP[i][i];
    }


    for (int sz{2}; sz <= K; ++sz) {
      for (int left{1}; left + sz - 1 <= K; ++left) {
        int right = left + sz - 1;
        DP[left][right] = 0x7FFFFFFF;
        for (int mid{left}; mid + 1 <= right; ++mid) {
          DP[left][right] = std::min(DP[left][right], DP[left][mid] + DP[mid + 1][right] + sum[right] - sum[left - 1]);
        }
      }
    }

    std::cout << DP[1][K] - sum[K] << '\n';
  }
}