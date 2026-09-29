#include <algorithm>
#include <iostream>
#include <vector>

int A[100'001];               // 입력 데이터 A
std::vector<int> T[400'001];  // segment tree T

// merge sort tree를 생성하는 함수
// Args:
//   Tidx  (int) : segment tree에서 A[start..end]구간을 의미하는 index
//   start (int), end (int) : A[start..end] 구간에 대한 merge sort tree를 구하고
//   있음을 나타내는 수
// Return:
//   A[start..end]을 정렬한 vector
std::vector<int>& construct(int Tidx, int start, int end) {
  if (start == end) {
    T[Tidx].push_back(A[start]);
    return T[Tidx];
  }
  int mid = start + ((end - start) >> 1);
  auto lhs = construct(Tidx << 1, start, mid);
  auto rhs = construct((Tidx << 1) | 1, mid + 1, end);

  T[Tidx].resize(lhs.size() + rhs.size());
  std::merge(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), T[Tidx].begin());
  return T[Tidx];
}

// A[i..j] 구간에서 k보다 작은 수의 개수를 구하는 함수
int query(int i, int j, int k, int Tidx, int start, int end) {
  if (j < start || end < i) return 0;
  if (i <= start && end <= j) {
    return std::distance(T[Tidx].begin(),
                         std::upper_bound(T[Tidx].begin(), T[Tidx].end(), k));
  }
  int mid = start + ((end - start) >> 1);
  return query(i, j, k, Tidx << 1, start, mid) +
         query(i, j, k, (Tidx << 1) | 1, mid + 1, end);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n, m;
  std::cin >> n >> m;
  for (int i{1}; i <= n; i++) std::cin >> A[i];
  construct(1, 1, n);

  auto print = [](const auto& rem, auto& list) {
    size_t size{list.size()};
    std::cout << rem << '[';
    for (size_t i{0}; i < size; i++) {
      std::cout << list[i] << ((i == size - 1) ? "]\n" : ", ");
    }
  };

  for (int i{1}; i < 10; i++) {
    print("MST : ", T[i]);
  }

  for (int query_count{0}; query_count < m; query_count++) {
    int i, j, k;
    std::cin >> i >> j >> k;
    // parametric search 이용
    int left{-1'000'000'007}, right{1'000'000'007};
    int mid = left + ((right - left) >> 1);
    while (left <= right) {
      mid = left + ((right - left) >> 1);
      if (query(i, j, mid, 1, 1, n) < k) left = mid + 1;
      else right = mid - 1;
    }
    std::cout << left << '\n';
  }
}