#pragma GCC optimize("O3")
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>

int N, Q, sqrtN;
std::vector<int> A;
std::vector<int> temp;

int counter[1'000'001];

struct query {
  int s;
  int e;
  int idx;

  bool operator<(query& o) {
    if (s / sqrtN == o.s / sqrtN) return e < o.e;
    return s / sqrtN < o.s / sqrtN;    
  }
};

query queries[1'000'001];
int ans[1'000'001];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N; sqrtN = static_cast<int>(std::sqrt(N));
  A.resize(N + 1); temp.resize(N + 1);
  for (int i{1}; i <= N; ++i) {
    std::cin >> A[i];
    temp[i] = A[i];
  }
  
  std::sort(temp.begin() + 1, temp.end());
  temp.erase(std::unique(temp.begin() + 1, temp.end()), temp.end());
  for (int i{1}; i <= N; ++i)
    A[i] = std::lower_bound(temp.begin(), temp.end(), A[i]) - temp.begin();

  std::cin >> Q;
  for (int i{1}; i <= Q; ++i) {
    int l, r;
    std::cin >> l >> r;
    queries[i] = {l, r, i};
  }

  std::sort(queries + 1, queries + 1 + Q);

  int now{0};
  int s{queries[1].s}, e{queries[1].e};
  for (int i{s}; i <= e; ++i) {
    if (counter[A[i]]++ == 0) ++now;
  }
  ans[queries[1].idx] = now;

  for (int i{2}; i <= Q; ++i) {
    while (queries[i].s < s) {
      --s;
      if (counter[A[s]]++ == 0) ++now;
    }
    while (e < queries[i].e) {
      ++e;
      if (counter[A[e]]++ == 0) ++now;
    }
    while (s < queries[i].s) {
      if (--counter[A[s]] == 0) --now;
      ++s;
    }
    while (queries[i].e < e) {
      if (--counter[A[e]] == 0) --now;
      --e;
    }

    ans[queries[i].idx] = now;
  }

  for (int i{1}; i <= Q; ++i) {
    std::cout << ans[i] << '\n';
  }
}