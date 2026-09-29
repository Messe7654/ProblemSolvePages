#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<int> numbers(N + 1);
  std::vector<int> delta(N + 1);

  for (int i{0}; i < N; ++i) std::cin >> numbers[i];
  std::sort(numbers.begin(), std::prev(numbers.end()));
  for (int i{1}; i < N; ++i) delta[i] = numbers[i] - numbers[i - 1];

  long long ans{0};
  for (int i{1}; i < N + 1; i += 2) ans += delta[i];

  long long min{0x7FFFFFFFFFFFFFFLL};
  for (int i{N}; i - 1 > 0; i -= 2) {
    ans += delta[i - 1] - delta[i];
    min = std::min(min, ans);
  }

  std::cout << min << '\n';
}