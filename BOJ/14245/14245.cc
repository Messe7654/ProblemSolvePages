#include <iostream>

#ifdef ONLINE_JUDGE
constexpr bool local = false;
#else
constexpr bool local = true;
#endif

#define DEBUG(rem) if constexpr (local) std::cout << rem

int A[500'001];
int T[2'000'001];

void Setup(int Tidx, int start, int end, int Aidx, int val) {
  if (Aidx < start || end < Aidx) return;

  if (start == end) {
    T[Tidx] = val;
    return;
  }

  int mid = start + ((end - start) >> 1);

  Setup(Tidx << 1, start, mid, Aidx, val);
  Setup(Tidx << 1 | 1, mid + 1, end, Aidx, val);
}

void RangeXOR(int Tidx, int start, int end, int left, int right, int val) {
  if (T[Tidx] != 0) {
    if (start != end) {
      T[Tidx << 1] ^= T[Tidx];
      T[Tidx << 1 | 1] ^= T[Tidx];
      T[Tidx] = 0;
    }
  }
  if (right < start || end < left) return;
  if (left <= start && end <= right) {
    T[Tidx] ^= val;
    return;
  }
  if (start == end) {
    T[Tidx] ^= val;
    return;
  }
  int mid = start + ((end - start) >> 1);
  RangeXOR(Tidx << 1, start, mid, left, right, val);
  RangeXOR(Tidx << 1 | 1, mid + 1, end, left, right, val);
}

int Get(int Tidx, int start, int end, int Aidx) {
  if (T[Tidx] != 0) {
    if (start != end) {
      T[Tidx << 1] ^= T[Tidx];
      T[Tidx << 1 | 1] ^= T[Tidx];
      T[Tidx] = 0;
    }
  }
  if (Aidx < start || end < Aidx) return 0;
  if (start == end) return T[Tidx];

  int mid = start + ((end - start) >> 1);

  return Get(Tidx << 1, start, mid, Aidx) ^ Get(Tidx << 1 | 1, mid + 1, end, Aidx);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  for (int i{1}; i <= N; ++i) std::cin >> A[i];
  for (int i{1}; i <= N; ++i) Setup(1, 1, N, i, A[i]);

  DEBUG("Constructed Segment Tree is : [");
  for (int i{1}; i <= (N << 2); ++i) {
    DEBUG("") << T[i] << ((i == (N << 2)) ? "]\n" : " ");
  }

  int M; std::cin >> M;
  for (int i{0}; i < M; ++i) {
    int t; std::cin >> t;
    if (t == 1) {
      int a, b, c;
      std::cin >> a >> b >> c;
      RangeXOR(1, 1, N, ++a, ++b, c);
    }
    else {
      int a;
      std::cin >> a;
      std::cout << Get(1, 1, N, ++a) << '\n';
    }
  }
}