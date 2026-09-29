#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;

  for (int testcase{1}; testcase <= T; ++testcase) {
    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<int> money(N);
    for (int& i : money) std::cin >> i;

    int sum{0}, ans{0};
    for (int i{0}; i < M - 1; ++i) sum += money[i];
    
    for (int i{0}; i < N; ++i) {
      sum += money[(i + M - 1) % N];
      if (sum < K) ++ans;
      if (N == M) break;
      sum -= money[i];
    }

    std::cout << ans << '\n';
  }

}