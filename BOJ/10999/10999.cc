#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(std::size_t n);

  template<class InputIt>
  SegmentTree(InputIt first, InputIt last);

  long long Query(std::size_t left, std::size_t right);

  void Push(std::size_t left, std::size_t right, long long augment);
  
 private:
  void __LazyPropagation(std::size_t idx);
  inline std::size_t __SetSize(std::size_t idx);

  std::size_t bias;
  std::size_t capacity;
  int height;

  std::vector<long long> T;
  std::vector<long long> L;
};

SegmentTree::SegmentTree(std::size_t n) {
  for (int i{1}; i < 64; ++i) n |= n >> i;
  ++n;
  bias = n;
  capacity = bias << 1;
  height = 63 - __builtin_clzll(bias);

  T.resize(capacity << 1);
  L.resize(capacity << 1);
}

template<class InputIt>
SegmentTree::SegmentTree(InputIt first, InputIt last) {
  std::size_t n = std::distance(first, last);

  for (int i{1}; i < 64; ++i) n |= n >> i;
  ++n;
  bias = n;
  capacity = bias << 1;
  height = 63 - __builtin_clzll(bias);

  T.resize(capacity << 1);
  L.resize(capacity << 1);

  std::copy(first, last, T.begin() + bias);
  for (std::size_t idx{bias - 1}; idx > 0; --idx) {
    T[idx] = T[idx << 1] + T[idx << 1 | 1];
  }
}

void SegmentTree::Push(std::size_t left, std::size_t right, long long augment) {
  for (int i{height}; i > 0; --i) {
    if (i > __builtin_ctzll(left | bias)) __LazyPropagation((left | bias) >> i);
    if (i > __builtin_ctzll(~(right | bias))) __LazyPropagation((right | bias) >> i);
  }

  for (std::size_t l{left | bias}, r{right | bias}; l <= r;) {
    auto set_size = __SetSize(l);
    if (l & 1)  { T[l] += augment * static_cast<long long>(set_size); L[l] += augment; }
    if (~r & 1) { T[r] += augment * static_cast<long long>(set_size); L[r] += augment; }
    l = (l + 1) >> 1;
    r = (r - 1) >> 1;
  }  

  for (int i{1}; i <= height; ++i) {
    if (i > __builtin_ctzll(left | bias))
      T[(left | bias) >> i] = T[(left | bias) >> i << 1] + T[(left | bias) >> i << 1 | 1];
    if (i > __builtin_ctzll(~(right | bias)))
      T[(right | bias) >> i] = T[(right | bias) >> i << 1] + T[(right | bias) >> i << 1 | 1];
  }
}

long long SegmentTree::Query(std::size_t left, std::size_t right) {
  for (int i{height}; i > 0; --i) {
    if (i > __builtin_ctzll(left | bias)) __LazyPropagation((left | bias) >> i);
    if (i > __builtin_ctzll(~(right | bias))) __LazyPropagation((right | bias) >> i);
  }

  long long ret{0};

  for (std::size_t l{left | bias}, r{right | bias}; l <= r;) {
    if (l & 1) ret += T[l];
    if (~r & 1) ret += T[r];
    l = (l + 1) >> 1;
    r = (r - 1) >> 1;
  }

  return ret;
}

void SegmentTree::__LazyPropagation(std::size_t idx) {
  if (L[idx] == 0) return;
  if (idx >= bias) { L[idx] = 0; return; }
  std::size_t subset_size = __SetSize(idx << 1);
  T[idx << 1    ] += L[idx] * static_cast<long long>(subset_size); L[idx << 1    ] += L[idx];
  T[idx << 1 | 1] += L[idx] * static_cast<long long>(subset_size); L[idx << 1 | 1] += L[idx];
  L[idx] = 0;
}

inline std::size_t SegmentTree::__SetSize(std::size_t idx) {
  return bias >> (63 - __builtin_clzll(idx));
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M, K;
  std::cin >> N >> M >> K;

  std::vector<long long> A(N);
  for (auto& elem : A) std::cin >> elem;

  SegmentTree seg(A.begin(), A.end());

  while (M + K > 0) {
    int a; std::cin >> a;

    if (a == 1) {
      int b, c, d;
      std::cin >> b >> c >> d;
      seg.Push(--b, --c, d);
      --M;
    }
    else if (a == 2) {
      int b, c;
      std::cin >> b >> c;
      std::cout << seg.Query(--b, --c) << '\n';
      --K;
    }
    // assert(false);
  }
}