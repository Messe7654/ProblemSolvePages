#include <iostream>
#include <bitset>

unsigned NextPerm(unsigned int n) {
	unsigned t = n | n - 1;
	return t + 1 | ((~t & t + 1) - 1) >> (__builtin_ctz(n) + 1);
}

int N;
int W[16][16];
long long DP[16][1 << 16];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;

  for (unsigned state{0}; state < (1U << N); ++state) {
    for (int i{0}; i < N; ++i) {
      DP[i][state] = 0x7FFFFFFF;
    }
  }

  for (int i{0}; i < N; ++i) {
    for (int j{0}; j < N; ++j) {
      std::cin >> W[i][j];
    }
  }

  for (int next{1}; next < N; ++next) {
    unsigned state = 1;
    if (W[0][next] != 0) DP[next][state | (1U << next)] = W[0][next];
  }

  for (int pop_count{2}; pop_count < N; ++pop_count) {
    unsigned state = 0;
    for (int j{0}; j < pop_count; ++j) state |= 1 << j;
    while (state < (1U << N)) {
      for (int now{1}; now < N; ++now) {
        for (int next{1}; next < N; ++next) {
          if (W[now][next] == 0) continue;
          if (state & (1U << now) && ~state & (1U << next))
            DP[next][state | (1U << next)] = std::min(DP[next][state | (1U << next)], DP[now][state] + W[now][next]);
        }
      }
      state = NextPerm(state);
    }
  }
  long long ans = 0x7FFFFFFF;
  for (int now{1}; now < N; ++now) {
    if (W[now][0] != 0) ans = std::min(DP[now][(1U << N) - 1] + W[now][0], ans);
  }

  std::cout << ans;
}