#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N;
  std::cin >> N;

  std::vector<std::pair<int, int>> A(N);
  std::vector<std::pair<int, int>> B(N);

  for (int i{0}; i < N; ++i) {
    A[i].first = i;
    std::cin >> A[i].second;
  }

  for (int i{0}; i < N; ++i) {
    B[i].first = i;
    std::cin >> B[i].second;
  }

  std::sort(A.begin(), A.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.second < rhs.second;
  });

  std::sort(B.begin(), B.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.second < rhs.second;
  });

  auto IsAngry = [&]() -> bool {
    for (int i{0}; i < N; ++i) {
      if (A[i].second > B[i].second) return true;
    }
    return false;
  };

  if (IsAngry()) { std::cout << "-1\n"; exit(0); }
  
  for (int i{0}; i < N; ++i) A[i].second = B[i].second;
  std::sort(A.begin(), A.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.first < rhs.first;
  });

  for (int i{0}; i < N; ++i)
    std::cout << A[i].second << ((i + 1 == N) ? '\n' : ' ');
}