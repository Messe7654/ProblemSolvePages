#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n;
  std::cin >> n;
    
  int ans{0}, max{-1'001};

  for (int i{0}; i < n; ++i) {
    int x;
    std::cin >> x;
    ans = std::max(ans + x, x);
    max = std::max(ans, max);
  }
  std::cout << max;
}