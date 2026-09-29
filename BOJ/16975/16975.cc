#include <iostream>

int N, M;
long long T[400'001];
long long L[400'001];
int A[100'001];

void Construct(int Tidx, int start, int end) {
  if (start == end) {
    T[Tidx] = A[start];
    return;
  }

  int mid = start + ((end - start) >> 1);
  Construct(Tidx << 1, start, mid);
  Construct(Tidx << 1 | 1, mid + 1, end);
  T[Tidx] = T[Tidx << 1] + T[Tidx << 1 | 1];
}

void Update(int Tidx, int start, int end, int left, int right, int aug) {
  if (L[Tidx] != 0) {
    T[Tidx] += (end - start + 1) * L[Tidx];
    if (start != end) {
      L[Tidx << 1] += L[Tidx];
      L[Tidx << 1 | 1] += L[Tidx];
    }
    L[Tidx] = 0;
  }

  if (right < start || end < left) return;
  if (left <= start && end <= right) {
    T[Tidx] += (end - start + 1) * aug;
    if (start != end) {
      L[Tidx << 1] += aug;
      L[Tidx << 1 | 1] += aug;
    }
    return;
  }

  int mid = start + ((end - start) >> 1);
  Update(Tidx << 1, start, mid , left, right, aug);
  Update(Tidx << 1 | 1, mid + 1, end, left, right, aug);
}

long long Get(int Tidx, int start, int end, int Aidx) {
  if (L[Tidx] != 0) {
    T[Tidx] += (end - start + 1) * L[Tidx];
    if (start != end) {
      L[Tidx << 1] += L[Tidx];
      L[Tidx << 1 | 1] += L[Tidx];
    }
    L[Tidx] = 0;
  }

  if (Aidx < start || end < Aidx) return 0;
  if (start == end) return T[Tidx];
  int mid = start + ((end - start) >> 1);
  return Get(Tidx << 1, start, mid, Aidx) + Get(Tidx << 1 | 1, mid + 1, end, Aidx);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::cin >> N;
  for (int i{1}; i <= N; i++) std::cin >> A[i];
  Construct(1, 1, N);

  std::cin >> M;
  for (int q{0}; q < M; q++) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int i, j, k;
      std::cin >> i >> j >> k;
      Update(1, 1, N, i, j, k);
    } else {
      int x;
      std::cin >> x;
      std::cout << Get(1, 1, N, x) << '\n';
    }
  }
}