#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>

int N, C, K, sqrtN;
int A[300'001];

struct query {
  int a;
  int b;
  int idx;

  bool operator<(query& other) {
    if (a / sqrtN == other.a / sqrtN) return b < other.b;
    return a / sqrtN < other.a / sqrtN;
  }
};

query queries[10'001];
int res[10'001];
int counter[10'001];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N >> C;
  for (int i{1}; i <= N; ++i) std::cin >> A[i];
  std::cin >> K;
  for (int i{1}; i <= K; ++i) {
    int a, b;
    std::cin >> a >> b;
    queries[i] = {a, b, i};
  }

  sqrtN = std::sqrt(N);
  std::sort(queries + 1, queries + 1 + K);

  int s{queries[1].a}, e{queries[1].b};
  for (int i{s}; i <= e; ++i) ++counter[A[i]];

  auto result = [&]() -> int {
    int ans{0};
    int acc{e - s + 1};
    for (int color{1}; color <= C; ++color) {
      if (counter[color] > (acc >> 1)) return color;
    }
    return 0;
  };

  res[queries[1].idx] = result();

  for (int i{2}; i <= K; ++i) {
    while (queries[i].a < s) {
      --s;
      ++counter[A[s]];
    }
    while (e < queries[i].b) {
      ++e;
      ++counter[A[e]];
    }
    while (s < queries[i].a) {
      --counter[A[s]];
      ++s;
    }
    while (queries[i].b < e) {
      --counter[A[e]];
      --e;
    }
    res[queries[i].idx] = result();
  }

  for (int i{1}; i <= K; ++i) {
    if (res[i] == 0) std::cout << "no\n";
    else std::cout << "yes " << res[i] << '\n';
  }
}