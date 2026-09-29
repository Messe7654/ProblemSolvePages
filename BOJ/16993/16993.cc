#include <algorithm>
#include <iostream>
#include <vector>

constexpr int MIN = -100'000'001;

int A[100'001];
int sum[100'001];
struct info {
  int lhs;
  int rhs;
  int max;
};

info tree[400'001];

void construct(int Tidx, int start, int end) {
  if (start == end) {
    tree[Tidx] = {A[start], A[start], A[start]};
    return;
  }
  int mid = start + ((end - start) >> 1);
  int right_index{Tidx << 1 | 1}, left_index{Tidx << 1};
  construct(left_index, start, mid);
  construct(right_index, mid + 1, end);
  tree[Tidx] = {
      std::max(tree[left_index].lhs, sum[mid] - sum[start - 1] + tree[right_index].lhs),
      std::max(tree[left_index].rhs + sum[end] - sum[mid], tree[right_index].rhs),
      std::max({tree[left_index].max, tree[right_index].max,
                tree[left_index].rhs + tree[right_index].lhs})
  };
}

info query(int Tidx, int start, int end, int left, int right) {
  if (end < left || right < start) return {MIN, MIN, MIN};
  if (left <= start && end <= right) return tree[Tidx];
  int mid = start + ((end - start) >> 1);
  auto lhs = query(Tidx << 1, start, mid, left, right);
  auto rhs = query(Tidx << 1 | 1, mid + 1, end, left, right);
  return {
    std::max(lhs.lhs, sum[mid] - sum[start - 1] + rhs.lhs),
    std::max(lhs.rhs + sum[end] - sum[mid], rhs.rhs),
    std::max({lhs.max, rhs.max, lhs.rhs + rhs.lhs})
  };
}
int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N;
  for (int i{1}; i <= N; i++) {
    std::cin >> A[i];
    sum[i] = sum[i - 1] + A[i];
  }
  construct(1, 1, N);
  std::cin >> M;
  while (M-- != 0) {
    int i, j;
    std::cin >> i >> j;
    std::cout << query(1, 1, N, i, j).max << '\n';
  }
}