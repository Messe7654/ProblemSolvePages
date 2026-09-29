#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>

int N, C, T, sqrtN;
int A[100'001];

struct query {
  int a;
  int b;
  int idx;

  bool operator<(query& other) {
    if (a / sqrtN == other.a / sqrtN) return b < other.b;
    return a / sqrtN < other.a / sqrtN;
  }
};

query queries[100'001];
long long res[100'001];
int counter[1'000'001];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N >> T;
  for (int i{1}; i <= N; ++i) std::cin >> A[i];
  for (int i{1}; i <= T; ++i) {
    int a, b;
    std::cin >> a >> b;
    queries[i] = {a, b, i};
  }

  sqrtN = std::sqrt(N);
  std::sort(queries + 1, queries + 1 + T);

  int s{queries[1].a}, e{queries[1].b};
  long long ans{0};
  for (int i{s}; i <= e; ++i) {
    ans -= 1LL * counter[A[i]] * counter[A[i]] * A[i];
    ++counter[A[i]];
    ans += 1LL * counter[A[i]] * counter[A[i]] * A[i];
  }
  res[queries[1].idx] = ans;

  for (int i{2}; i <= T; ++i) {
    while (queries[i].a < s) {
      --s;
      ans -= 1LL * counter[A[s]] * counter[A[s]] * A[s];
      ++counter[A[s]];
      ans += 1LL * counter[A[s]] * counter[A[s]] * A[s];
    }
    while (e < queries[i].b) {
      ++e;
      ans -= 1LL * counter[A[e]] * counter[A[e]] * A[e];
      ++counter[A[e]];
      ans += 1LL * counter[A[e]] * counter[A[e]] * A[e];
    }
    while (s < queries[i].a) {
      ans -= 1LL * counter[A[s]] * counter[A[s]] * A[s];
      --counter[A[s]];
      ans += 1LL * counter[A[s]] * counter[A[s]] * A[s];
      ++s;
    }
    while (queries[i].b < e) {
      ans -= 1LL * counter[A[e]] * counter[A[e]] * A[e];
      --counter[A[e]];
      ans += 1LL * counter[A[e]] * counter[A[e]] * A[e];
      --e;
    }
    res[queries[i].idx] = ans;
  }

  for (int i{1}; i <= T; ++i) {
    std::cout << res[i] << '\n';
  }
}