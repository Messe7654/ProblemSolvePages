#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  struct info {
    int L;
    int H;
    int R;
  };

  std::vector<info> infos(N);

  for (int i{0}; i < N; ++i) {
    std::cin >> infos[i].L >> infos[i].H >> infos[i].R;
  }

  std::sort(infos.begin(), infos.end(), [](const auto& lhs, const auto& rhs) {
    if (lhs.L != rhs.L) return lhs.L < rhs.L;
    if (lhs.H != rhs.H) return lhs.H > rhs.H;
    return lhs.R > rhs.R;
  });

  std::deque<info> deque;
  for (const auto& now : infos) {
    while (deque.empty() != true && deque.front().R < now.L) {
      std::cout << deque.front().R << ' ' << deque.front().H << '\n';
      deque.pop_front();
    }
    while (deque.empty() != true && deque.back().R < now.R && deque.back().H < now.H) {
      deque.pop_back();
    }
    if (deque.empty() || !(deque.back().H > now.H && deque.back().R > now.R)) 
      deque.push_front(now);
  }
}