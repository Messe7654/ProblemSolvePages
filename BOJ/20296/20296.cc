#include <algorithm>
#include <iostream>
#include <vector>

long long factorial[1'010'101] = { 1, 1, };
constexpr long long MOD = 1'000'000'007;

long long pow_(long long a, long long b) {
	if (b == 0) return 1;
	a = a % MOD;
	long long ret{ 1LL };
	while (b != 0) {
		if (b & 1) ret = (ret * a) % MOD;
		a = (a * a) % MOD;
		b = b >> 1;
	}
	return ret;
}

long long C(int n, int r) {
	if (r == n || r == 0) return 1;
	return (1LL * factorial[n] * pow_(1LL * factorial[r] * factorial[n - r], MOD - 2)) % MOD;
}

long long H(int n, int r) {
	if (r < 0) return 0;
	return C(n + r - 1, r);
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	for (int i{ 2 }; i < 1'010'101; i++) {
		factorial[i] = (1LL * factorial[i - 1] * i) % MOD;
	}

	int N, m, M, K;
	std::cin >> N >> m >> M >> K;

	long long ans{ 0 };
	for (int i{ 0 }; i <= N; i++) {
		ans = (MOD + ans + ((i & 1) ? -1LL : 1LL) * C(N, i) * H(N, K - (N - i) * m - i * (M + 1))) % MOD;
	}

	std::cout << ans;
}