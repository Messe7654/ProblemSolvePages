#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);
  std::map<int, std::vector<int>> A, B;
  int N; std::cin >> N;
  
  for (int i{0}; i < N; ++i) {
    int a; std::cin >> a;
    if (!A.contains(a)) A[a] = std::vector<int>();
    A[a].push_back(i);
  }
  
  int M; std::cin >> M;
  
  for (int i{0}; i < M; ++i) {
    int b; std::cin >> b;
    if (!B.contains(b)) B[b] = std::vector<int>();
    B[b].push_back(i);
  }

  int A_idx{-1}, B_idx{-1};
  auto A_it{A.rbegin()}, B_it{B.rbegin()};
  std::vector<int> ans;

  while (A_idx < N && B_idx < M && A_it != A.rend() && B_it != B.rend()) {
    const auto& [A_view, A_list] = *A_it;
    const auto& [B_view, B_list] = *B_it;
    if (A_view < B_view) ++B_it;
    else if (B_view < A_view) ++A_it;
    else {
      auto A_upper = std::upper_bound(A_list.begin(), A_list.end(), A_idx);
      auto B_upper = std::upper_bound(B_list.begin(), B_list.end(), B_idx);
      auto A_valid_count = std::distance(A_upper, A_list.end());
      auto B_valid_count = std::distance(B_upper, B_list.end());
      int count = std::min(A_valid_count, B_valid_count);
      if (count) {
        ans.insert(ans.end(), count, A_view);
        A_idx = *(A_upper + count - 1);
        B_idx = *(B_upper + count - 1);
      }
      ++A_it; ++B_it;
    }
  }

  int size = static_cast<int>(ans.size());
  std::cout << size << '\n';
  for (int i{0}; i < size; ++i) {
    std::cout << ans[i] << ((i + 1 == size) ? '\n' : ' ');
  }
}