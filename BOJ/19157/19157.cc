#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, Q;
  std::cin >> N >> Q;
  std::vector<int> R(N), C(N);

  bool prev, curr;
  int x;
  std::cin >> x;
  prev = (x % 2 == 0);
  for (int i{1}; i < N; ++i) {
    std::cin >> x;
    curr = (x % 2 == 0);
    R[i] = R[i - 1] + (curr != prev);
    prev = curr;
  }

  std::cin >> x;
  prev = (x % 2 == 0);
  for (int i{1}; i < N; ++i) {
    std::cin >> x;
    curr = (x % 2 == 0);
    C[i] = C[i - 1] + (curr != prev);
    prev = curr;
  }
  
  for (int query_idx{0}; query_idx < Q; ++query_idx) {
    int r1, r2, c1, c2;
    std::cin >> r1 >> c1 >> r2 >> c2;
    --r1; --r2; --c1; --c2;
    std::cout << (((R[r1] == R[r2]) && (C[c1] == C[c2])) ? "YES\n" : "NO\n");
  }
}