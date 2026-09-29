#include <algorithm>
#include <iostream>
#include <deque>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;

  std::deque<int> deque(N);
  std::generate(deque.begin(), deque.end(), [n = (int)0]() mutable { return ++n; });
  auto now = deque.begin();
  std::size_t ans{0};
  std::size_t size(deque.size());
  for (int i{0}; i < M; ++i) {
    int x; std::cin >> x;
    auto target = std::find(deque.begin(), deque.end(), x);
    ans += std::min((std::distance(now, target) + size) % size, (std::distance(target, now) + size) % size);
    now = deque.erase(target);
    --size;
  }

  std::cout << ans;
}