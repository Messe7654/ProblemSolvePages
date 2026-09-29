#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

void push(std::map<int, int>& map, int x) {
  if (map.find(x) == map.end()) map[x] = 0;
  ++map[x];
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, C;
  std::cin >> N >> C;

  std::vector<int> weight(N);
  for (auto& w : weight) std::cin >> w;
  
  // if (C == 0) { std::cout << 1; exit(0); }
  
  std::map<int, int> lhs, rhs;

  // for Left
  int mid = N / 2;
  for (unsigned b{0}; b < (1U << mid); ++b) {
    unsigned copy{b};
    int sum{0};
    while (copy && sum <= C) {
      auto lsb = copy & (~copy + 1);
      int idx = __builtin_ctz(lsb);
      sum += weight[idx];      
      copy &= ~lsb;
    }
    if (sum <= C) push(lhs, sum);
  }

  // for Right
  for (unsigned b{0}; b < (1U << (N - mid)); ++b) {
    unsigned copy{b};
    int sum{0};
    while (copy && sum <= C) {
      auto lsb = copy & (~copy + 1);
      int idx = __builtin_ctz(lsb) + mid;
      sum += weight[idx];
      copy &= ~lsb;
    }
    if (sum <= C) push(rhs, sum);
  }
  
  std::for_each(rhs.begin(), rhs.end(), [total = 0](auto& x) mutable {
    x.second += total;
    total = x.second;
  });
  
  long long ans = std::accumulate(lhs.begin(), lhs.end(), 0LL, [C, rhs](long long T, auto& x) {
    auto ub = rhs.upper_bound(C - x.first);
    if (ub == rhs.begin()) return T;
    
    return T + x.second * (--ub)->second;
  });  

  std::cout << ans;
}