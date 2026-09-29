#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::unordered_map<int, int> counter;
  for (int i{0}; i < N; i++) {
    int number; std::cin >> number;
    ++counter[number];
  }

  for (int i{-1'000'000}; i <= 1'000'000; i++) {
    if (counter.find(i) != counter.end()) {
      auto count = counter[i];
      for (int c{0}; c < count; c++) std::cout << i << '\n';
    } 
  }
}