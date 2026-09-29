#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

std::map<std::pair<long long, int>, int> map;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, K;
  std::cin >> N >> K;

  for (int i{0}; i < N; ++i) {
    int a; std::cin >> a;
    std::queue<std::pair<std::pair<long long, int>, int>> queue;
    queue.push({{a, 1}, 1});
    for (auto [p, val] : map) {
      queue.push({{p.first + a, p.second + 1}, val});
    }

    while (queue.empty() != true) {
      auto [p, v] = queue.front();
      map[p] += v;
      queue.pop();
    }
  }

  int ans{0};
  for (auto [p, v] : map) {
    std::cout << p.first << ' ' << p.second << ' ' << v << '\n';
    if (p.first == p.second * K) ans += v;
  }

  std::cout << ans;
}