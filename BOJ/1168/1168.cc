#include <iostream>

int tree[400'001];
int ans[100'001];
int N, K;

int update(int Tidx, int start, int end, int index, int value) {
  if (index < start || end < index) return tree[Tidx];
  if (start == end) return tree[Tidx] = value;
  int mid = start + ((end - start) >> 1);
  auto lhs = update(Tidx << 1, start, mid, index, value);
  auto rhs = update(Tidx << 1 | 1, mid + 1, end, index, value);
  return tree[Tidx] = lhs + rhs;
}

void push(int value) { update(1, 1, N, value, 1); }

void pop(int value) { update(1, 1, N, value, 0); }

int query(int value) {
  int Tidx{1}, start{1}, end{N};
  while (start < end) {
    int mid = start + ((end - start) >> 1);
    if (tree[Tidx << 1] < value) {
      value -= tree[Tidx << 1];
      Tidx = Tidx << 1 | 1;
      start = mid + 1;
    } else {
      Tidx = Tidx << 1;
      end = mid;
    }
  }
  return start;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N >> K;
  for (int i{1}; i <= N; i++) push(i);
  ans[0] = K;
  pop(K);
  int pos{K - 1};
  for (int i{1}; i < N; i++) {
    pos = (pos + K - 1) % (N - i);
    ans[i] = query(pos + 1);
    pop(ans[i]);
  }

  std::cout << '<';
  for (int i{0}; i < N; i++) {
    std::cout << ans[i] << ((i + 1 == N) ? ">" : ", ");
  }
}