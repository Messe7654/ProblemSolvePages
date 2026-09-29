#include <algorithm>
#include <iostream>
#include <vector>

int N;
std::vector<int> T;
std::vector<int> pi;

void failure() {
  int i{1}, j{0};
  while (i < N) {
    if (T[i] == T[j]) {
      pi[i] = j + 1;
      ++i; ++j;
    }
    else if (j > 0) {
      j = pi[j - 1];
    }
    else {
      pi[i] = 0;
      ++i;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;
  T.resize(N);
  pi.resize(N);
  for (int i{N - 1}; i >= 0; --i) std::cin >> T[i];

  failure();

  std::vector<std::pair<int, int>> res;
  for (int k{0}; k < N; ++k) {
    res.emplace_back(N - k - 1, k + 1 - pi[k]);
  }

  std::sort(res.begin(), res.end(), [](const auto& lhs, const auto& rhs) {
    if (lhs.first + lhs.second == rhs.first + rhs.second) return lhs.second < rhs.second;
    return lhs.first + lhs.second < rhs.first + rhs.second;
  });
  
  std::cout << res[0].first << ' ' << res[0].second;
}