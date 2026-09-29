#include <iostream>

unsigned long long sum[51];
constexpr unsigned long long mod = 1'000'000'007;

unsigned long long power(unsigned long long base, unsigned long long exp) {
	if (exp == 0) return 1;
	if (exp & 1) return (base * power(base, exp - 1)) % mod;
	unsigned long long half = power(base, exp >> 1);
	return (half * half) % mod;
}

unsigned long long C[52][52];

unsigned long long bionomial(int a, int b) {
  if (a == b || b == 0 ) return C[a][b] = 1;
  if (C[a][b] != 0) return C[a][b];
  return C[a][b] = (bionomial(a - 1, b - 1) + bionomial(a - 1, b)) % mod;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, K; std::cin >> N >> K;
  sum[0] = N;

  for (int i{1}; i <= K; ++i) {
    sum[i] = (power(N + 1, i + 1) - 1 + mod) % mod;
    for (int j{0}; j < i; ++j) {
      sum[i] = (sum[i] + mod - (bionomial(i + 1, j) * sum[j]) % mod) % mod;
    }
    sum[i] = (sum[i] * power(i + 1, mod - 2)) % mod;
  }

  std::cout << sum[K];
}