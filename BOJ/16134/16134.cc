#include <algorithm>
#include <iostream>
#include <vector>

constexpr long long kMod = 1'000'000'007;

long long pow(long long a, int b) {
  if (b == 0) return 1;
  auto temp = pow(a, b >> 1);
  if (b & 1) return ((temp * temp) % kMod * a) % kMod;
  else  return (temp * temp) % kMod;
}

long long mod_inverse(long long a) {
  return pow(a, kMod - 2);
}

int main() {
  int N, R; std::cin >> N >> R;
  std::vector<long long> factorial(N + 1);
  factorial[0] = factorial[1] = 1;
  for (int i{2}; i <= N; ++i) factorial[i] = (factorial[i - 1] * i) % kMod;

  std::cout << (factorial[N] * mod_inverse((factorial[R] * factorial[N - R]) % kMod)) % kMod;
}