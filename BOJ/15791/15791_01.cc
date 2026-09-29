#include <iostream>
#include <tuple>

constexpr long long kMod = 1'000'000'007;

long long f[1'000'001] = {1, 1, 2, 6, 24, 120, };

template <typename T>
std::tuple<T, T, T> EXGCD(T a, T b) {
  if (b == 0) return {a, 1, 0};
  auto [g, x, y] = EXGCD(b, a % b);
  return {g, y, x - (a / b) * y};
}

template <typename T>
T ModInversion(T dividend, T divisor) {
  auto [g, x, y] = EXGCD(dividend, divisor);
  return (x % divisor + divisor) % divisor;
}

int Binom(int n, int r) {
  // (n r)^T = \frac{n!}{r!(n-r)!}
  long long ret = f[n];
  ret = (ret * ModInversion(f[r], kMod)) % kMod;
  ret = (ret * ModInversion(f[n - r], kMod)) % kMod;
  return static_cast<int>(ret);
}

int main() {
  int N, M;
  std::cin >> N >> M;

  for (int i{6}; i <= N; ++i) f[i] = (f[i - 1] * i) % kMod;
  std::cout << Binom(N, M) << '\n'; 
}