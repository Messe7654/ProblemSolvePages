#include <algorithm>
#include <iostream>

int numbers[1'000'001];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  for (int i{1}; i <= N; i++) std::cin >> numbers[i];
  std::sort(numbers + 1, numbers + N + 1);

  for (int i{1}; i <= N; i++) std::cout << numbers[i] << '\n';
}