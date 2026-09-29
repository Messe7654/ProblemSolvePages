#include <algorithm>
#include <iostream>
#include <queue>

template <typename T, typename Comp>
struct __pq {
  using value_type                = T;
  using compare_type              = Comp;
  using reference                 = value_type&;

  std::priority_queue<value_type, std::vector<value_type>, compare_type> real;
  std::priority_queue<value_type, std::vector<value_type>, compare_type> ir;

  bool empty() {
    __shirink_fit();
    return real.empty();
  }

  void insert(const value_type& val) { real.push(val); }
  void erase(const value_type& val) { ir.push(val); }
  
  value_type top() {
    __shirink_fit();
    return real.top();
  }

  value_type pop() {
    value_type temp = top();
    real.pop();
    return temp;
  }

  void __shirink_fit() { 
    while (!real.empty() && !ir.empty() && real.top() == ir.top()) { real.pop(); ir.pop(); }
  }
};

template <typename T>
struct dual_pq {
  using value_type                = T;

  __pq<value_type, std::greater<T>> min_pq;
  __pq<value_type, std::less<T>>    max_pq;

  void push(const value_type& x) { min_pq.insert(x); max_pq.insert(x); }

  void pop_max() {
    if (max_pq.empty()) return;
    int popped = max_pq.pop();
    min_pq.erase(popped);
  }

  void pop_min() {
    if (min_pq.empty()) return;
    int popped = min_pq.pop();
    max_pq.erase(popped);
  }

  std::pair<value_type, value_type> minmax() {
    return {min_pq.top(), max_pq.top()};
  }

  bool empty() {
    min_pq.__shirink_fit();
    max_pq.__shirink_fit();

    return min_pq.empty() && max_pq.empty();
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);
  
  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    int k; std::cin >> k;
    dual_pq<int> pq;

    for (int query{1}; query <= k; ++query) {
      char op; std::cin >> op;

      if ('D' == op) {
        int comp; std::cin >> comp;
        if (comp == 1) {
          pq.pop_max();
        }
        else if (comp == -1) {
          pq.pop_min();
        }
        continue;
      }
      if ('I' == op) {
        int n; std::cin >> n;
        pq.push(n);
        continue;
      }
    }

    if (pq.empty()) std::cout << "EMPTY\n";
    else {
      auto [min, max] = pq.minmax();
      std::cout << max << ' ' << min << '\n';
    }
  }
}