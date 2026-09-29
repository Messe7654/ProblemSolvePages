#include <iostream>

constexpr int mod = 10'000;

int DP[102][3];
int pre[102];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, K;
  std::cin >> N >> K;

  for (int i{0}; i < K; ++i) {
    int a, b;
    std::cin >> a >> b;
    pre[a] = b;
  }
  DP[0][0] = DP[0][1] = DP[0][2] = 1;

  for (int i{1}; i <= N; ++i) {
    if (pre[i] != 0) {
      
    }
    else {

    }
  }
}