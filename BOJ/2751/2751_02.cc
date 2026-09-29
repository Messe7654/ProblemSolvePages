#include <iostream>

int counter[2'000'001];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  for (int i{0}; i < N; i++) {
    int number; std::cin >> number;
    ++counter[number + 1'000'000];
  }

  for (int i{-1'000'000}; i <= 1'000'000; i++) {
    for (int j{0}; j < counter[i + 1'000'000]; j++) {
      std::cout << i << '\n';
    }
  }
}