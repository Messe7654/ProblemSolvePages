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

template <typename T>
T Pow(T base, int exp, T divisor) {
  if (exp == 0) return 1;
  T ret = (exp & 1) ? base : 1;
  T half = Pow(base, exp >> 1, divisor);
  ret = (((ret * half) % divisor) * half) % divisor;
  return ret;
}

int Binom1(int n, int r) {
  // (n r)^T = \frac{n!}{r!(n-r)!}
  long long ret = f[n];
  ret = (ret * ModInversion(f[r], kMod)) % kMod;
  ret = (ret * ModInversion(f[n - r], kMod)) % kMod;
  return static_cast<int>(ret);
}

int Binom2(int n, int r) {
  // (n r)^T = \frac{n!}{r!(n-r)!}
  long long ret = f[n];
  ret = (ret * Pow(f[r], kMod - 2, kMod)) % kMod;
  ret = (ret * Pow(f[n - r], kMod - 2, kMod)) % kMod;
  return ret;
}

int main() {
  int N, M;
  std::cin >> N >> M;

  for (int i{6}; i <= N; ++i) f[i] = (f[i - 1] * i) % kMod;
  std::cout << Binom2(N, M) << '\n'; 
}