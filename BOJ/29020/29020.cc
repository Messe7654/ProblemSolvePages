#include <algorithm>
#include <iostream>

long long func(int N, int D, int A, int B) {
  return 1LL * A * D - 1LL * B * D * (D - 1) / 2;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, D;
  while (std::cin >> N >> D) {
    if (N == 0 && D == 0) break;
    
    if (N == 1) {
      int A, B; std::cin >> A >> B;
      std::cout << func(N, D, A, B) << '\n';
      continue;
    }

    auto comp = [](const auto& lhs, const auto& rhs) {
      if (lhs.first == rhs.first) return lhs.second < rhs.second;
      return lhs.first > rhs.first;
    };
    
    std::pair<int, int> first{-1, 0}, second{-1, 0};
    for (int i{0}; i < N; ++i) {
      std::pair<int, int> game;
      std::cin >> game.first >> game.second;
      if (comp(game, first)) {
        second = first;
        first = game;
      }
      else if (comp(game, second)) {
        second = game;
      }
    }

    long long max{-1};
    for (int i{0}; 2 * i <= D; ++i) {
      max = std::max(func(N, D - 2 * i, first.first, first.second) + 1LL * (first.first + second.first) * i, max);
    }
    std::cout << max << '\n';
  }
}