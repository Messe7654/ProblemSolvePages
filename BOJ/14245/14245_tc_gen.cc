#include <bits/stdc++.h>

#include "testlib.h"

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  auto n = opt<int>(1);
  auto m = opt<int>(2);
  auto query_weight = opt<int>(3); // 크면 클수록 1번 쿼리 ++, 작으면 작을수록 2번 쿼리 --

  assert(0 < n && n <= 500'000);
  assert(0 < m && m <= 500'000);

  std::vector<int> A(n);
  for (int i{0}; i < n; ++i) {
    A[i] = rnd.next(100'001);
  }

  std::vector<std::vector<int>> queries(m);
  for (int i{0}; i < m; ++i) {
    if (rnd.wnext(2, query_weight)) {
      int a, b, c;
      a = rnd.next(n);
      b = rnd.next(n);
      c = rnd.next(100'001);
      if (a > b) std::swap(a, b);
      queries[i] = {1, a, b, c};
    }
    else {
      int a = rnd.next(n);
      queries[i] = {2, a};
    }
  }

  println(n);
  println(A);
  println(m);
  for (int i{0}; i < m; ++i) {
    println(queries[i]);
  }
}