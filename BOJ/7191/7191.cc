#include <iostream>
#include <vector>

std::vector<int> children[10'000];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, K; std::cin >> N >> K;
  for (int i{1}; i <= N; ++i) {
    int number_of_child;
    std::cin >> number_of_child;
    for (int j{0}; j < number_of_child; ++ j) {
      int c; std::cin >> c;
      children[i].push_back(c);
    }
  }
}