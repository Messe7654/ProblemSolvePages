#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, K;
  std::cin >> N >> K;

  std::vector<int> T(N + 1);
  std::unordered_map<int, int> counter;
  long long ans{0};
  for (int i{1}; i <= N; ++i) {
    ++counter[T[i - 1]];
    int x; std::cin >> x;
    T[i] = T[i - 1] + x;
    if (counter.find(T[i] - K) != counter.end()) ans += counter[T[i] - K];
  }
  std::cout << ans;
}