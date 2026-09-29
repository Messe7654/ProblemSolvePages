#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::string S;
  int K;
  std::cin >> S >> K;
  int size{static_cast<int>(S.size())};

  if (size * (size + 1) / 2 < K) {
    std::cout << -1;
    return 0;
  }

  struct entry {
    int index;
    std::string str;
  };

  struct comp {
    bool operator()(const entry& lhs, const entry& rhs) {
      return lhs.str > rhs.str;
    }
  };


  std::priority_queue<entry, std::vector<entry>, comp> pq;
  for (int i{0}; i < size; i++) {
    pq.push({i, std::string(S.begin() + i, S.end())});
  }

  while (pq.empty() != true) {
    std::cout << pq.top().str << ' ';
    pq.pop();
  }
}