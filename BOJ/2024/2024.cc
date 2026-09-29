#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> segments;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int M; std::cin >> M;

  int L, R;
  while (std::cin >> L >> R) {
    if (L == 0 && R == 0) break;
    segments.emplace_back(L, R);
    assert(L < R);
  }

  if (segments.empty()) {
    std::cout << 0;
    exit(0);
  }

  std::sort(segments.begin(), segments.end(), [](const auto& lhs, const auto& rhs) {
    if (lhs.first == rhs.first) return lhs.second > rhs.second;
    return lhs.first < rhs.first;
  });

  int end{0}, ans{0}, current_end{end};
  int size = static_cast<int>(segments.size());
  int idx{0};

  while (idx < size) {
    while (segments[idx].first <= end) {
      current_end = std::max(current_end, segments[idx].second);
      ++idx;
    }
    if (current_end <= end) break;
    end = current_end;
    ++ans;
    if (end >= M) break;
  }

  std::cout << ((end < M) ? 0 : ans);
}