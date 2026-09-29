#include <iostream>

constexpr long long kMod = 1'000'000'007;

class M {
 public:
  M();
  M(const M& other) { 
    for (int row{0}; row < 2; ++row) for (int col{0}; col < 2; ++col) arr[row][col] = other.arr[row][col];
  }

  static M mul(M a, M b);
  static M pow(M a, long long b);

  long long arr[2][2];
};

M::M() {
  arr[0][0] = arr[0][1] = arr[1][0] = arr[1][1] = 0;
}

M M::mul(M a, M b) {
  M temp;
  for (int row{0}; row < 2; ++row) {
    for (int col{0}; col < 2; ++col) {
      for (int t{0}; t < 2; ++t) {
        temp.arr[row][col] = (temp.arr[row][col] + a.arr[row][t] * b.arr[t][col]) % kMod;
      }
    }
  }
  return temp;
}

M M::pow(M a, long long b) {
  if (b == 1) return a;
  if (b & 1) return mul(a, pow(a, b - 1));
  M half = pow(a, b >> 1);
  return mul(half, half);
}


int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  long long N; std::cin >> N;
  M a;
  a.arr[0][0] = a.arr[0][1] = a.arr[1][0] = 1;
  auto res = M::pow(a, N);

  std::cout << res.arr[1][0];
}