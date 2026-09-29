#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

int Q[1'01];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M, T;  // N : 일렬로 나열된 구역의 수
                // M : 사회자가 정한 마릿수
                // T : 게임 제한 시간
  int P;        // P : 파댕이가 속해있는 무리의 위치 
  std::cin >> N >> M >> T;
  for (int i{1}; i <= N; i++) {
    std::cin >> Q[i];
  }
  std::cin >> P;
  std::unordered_set<int> right{Q[P]}, left{Q[P]};
  auto print = [](const std::string& rem, auto Container) -> void {
    std::cout << "DEBUG> " << rem << " [";
    auto it = Container.begin();
    while (it != Container.end()) {
      std::cout << *it << ((std::next(it) == Container.end()) ? "]\n" : ", ");
      it++;
    }
  };

  for (int i{1}; i < T; i++) {
    int index = (P + i - 1) % N + 1;
    std::vector<int> inserter(right.size());

    std::transform(right.cbegin(), right.cend(),
                   inserter.begin(),
                   [&index](int num){ return Q[index] + num; });
    right.insert(inserter.begin(), inserter.end());
  }
  for (int i{1}; i < T; i++) {
    int index = (P - i - 1 + N) % N + 1;
    std::vector<int> inserter(left.size());

    std::transform(left.cbegin(), left.cend(),
                   inserter.begin(),
                   [&index](int num){ return Q[index] + num; });
    left.insert(inserter.begin(), inserter.end());
  }

  std::cout << ((right.find(M) != right.end() || left.find(M) != left.end()) ?
                "YES\n" :
                "NO\n");
}