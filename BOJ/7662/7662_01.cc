#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);
  
  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    int k; std::cin >> k;
    std::multiset<int> Q;

    for (int query{1}; query <= k; ++query) {
      char op; std::cin >> op;

      if ('D' == op) {
        int comp; std::cin >> comp;
        if (Q.empty()) continue;
        if (comp == 1) {
          Q.erase(--Q.end());
        }
        else if (comp == -1) {
          Q.erase(Q.begin());
        }
        continue;
      }
      if ('I' == op) {
        int n; std::cin >> n;
        Q.insert(n);
        continue;
      }
    }

    if (Q.empty()) std::cout << "EMPTY\n";
    else std::cout << *(--Q.end()) << ' ' << *(Q.begin()) << '\n';
  }
}