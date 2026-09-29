#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#include <tuple>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<int> a(N + 1);
  std::vector<int> b(N + 1);
  std::vector<long long> s(N + 1);
  std::vector<double> time_points(N + 1);

  for (int i{1}; i <= N; ++i) std::cin >> a[i];
  for (int i{1}; i <= N; ++i) std::cin >> b[i];

  s[1] = 0; time_points[1] = 0;
  std::deque<int> C{1};

  for (int i{2}; i <= N; ++i) {
    while (C.size() > 1 && time_points[C[1]] <= a[i]) C.pop_front();
    s[i] = s[C.front()] + 1LL * b[C.front()] * a[i];
    while (C.empty() != true) {
      auto j = C.back();
      double time_point = static_cast<double>(s[i] - s[j]) / (b[j] - b[i]);
      if (time_point <= time_points[j]) C.pop_back();
      else {
        time_points[i] = time_point;
        C.push_back(i);
        break;
      }
    }
  }
  std::cout << s[N];
}