#include <iostream>
#include <map>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  std::map<int, int> height;

  height[-1] = height[N] = 0;
  long long ans{0};

  for (int i{0}; i < N; ++i) {
    int key; std::cin >> key;
    auto lhs = std::prev(height.lower_bound(key));
    auto rhs = height.upper_bound(key);
    auto curr_height = std::max(lhs->second, rhs->second) + 1;
    height[key] = curr_height;
    ans += curr_height;    
  }

  std::cout << ans << '\n';
}