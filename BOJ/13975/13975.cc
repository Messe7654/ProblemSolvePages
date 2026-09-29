#include <iostream>
#include <vector>
#include <queue>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    int K; std::cin >> K;
    auto pages = std::vector<int>(K);
    for (int& page: pages) std::cin>> page;
    int ans{0};

    auto pq = std::priority_queue(pages.begin(), pages.end(), std::greater<int>());
    while (pq.size() >= 2) {
      int a = pq.top(); pq.pop();
      int b = pq.top(); pq.pop();
      int temp = a + b;
      ans += temp;
      pq.push(temp);
    }
    std::cout << ans << '\n';
  }
}