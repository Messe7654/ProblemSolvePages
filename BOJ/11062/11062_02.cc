#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    int N; std::cin >> N;
    std::vector<int> cards(N);
    for (int i{0}; i < N; ++i) std::cin >> cards[i];

    auto cache = std::vector(N + 1, std::vector<int>(N + 1));
    auto solve = [&]() -> int {
      
    };
  }
}