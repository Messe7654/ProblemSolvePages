#include <algorithm>
#include <cassert>
#include <iostream>

int N, t[5'001];
int DP[5'001][10][10][10];

inline int func(int x, int y) { return std::min((10 - x + y) % 10, (10 + x - y) % 10); }

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;
  for (int i{1}; i <= N; ++i) std::cin >> t[i];

  for (int i{1}; i <= N; ++i)
    for (int idx1{0}; idx1 < 10; ++idx1)
      for (int idx2{0}; idx2 < 10; ++idx2)
        for (int idx3{0}; idx3 < 10; ++idx3)
          DP[i][idx1][idx2][idx3] = 0x7FFFFFFF;

  DP[1][t[1]][0][0] = DP[1][0][t[1]][0] =  DP[1][0][0][t[1]] = func(t[1], 0);

  for (int i{2}; i <= N; ++i) {
    for (int idx1{0}; idx1 < 10; ++idx1) {
      for (int idx2{0}; idx2 < 10; ++idx2) {
        for (int idx3{0}; idx3 < 10; ++idx3) {
          if (DP[i - 1][idx1][idx2][idx3] != 0x7FFFFFFF) {
            DP[i][t[i]][idx2][idx3] =
                std::min(DP[i][t[i]][idx2][idx3], DP[i - 1][idx1][idx2][idx3] + func(idx1, t[i]));
            DP[i][idx1][t[i]][idx3] =
                std::min(DP[i][idx1][t[i]][idx3], DP[i - 1][idx1][idx2][idx3] + func(idx2, t[i]));
            DP[i][idx1][idx2][t[i]] =
                std::min(DP[i][idx1][idx2][t[i]], DP[i - 1][idx1][idx2][idx3] + func(idx3, t[i]));
            
          }
        }
      }
    }
  }

  int min = 0x7FFFFFFF;
  for (int idx1{0}; idx1 < 10; ++idx1)
    for (int idx2{0}; idx2 < 10; ++idx2)
      for (int idx3{0}; idx3 < 10; ++idx3)
        min = std::min(DP[N][idx1][idx2][idx3], min);

  
  std::cout << min;
}