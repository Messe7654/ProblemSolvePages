#include <iostream>
#include <vector>
#include <map>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);
  
  std::map<char, int> encode;
  std::map<int, char> decode;

  auto initialize = [&]() -> void {
    int idx{0};
    for (char c{'A'}; c <= 'Z'; ++c) {
      encode[c] = idx;
      decode[idx] = c;
      ++idx;
    }
    for (char c{'a'}; c <= 'z'; ++c) {
      encode[c] = idx;
      decode[idx] = c;
      ++idx;
    }
  };
  initialize();

  auto parse = [](std::istream& in) -> std::pair<char, char> {
    char src, dst, tmp;
    in >> src >> tmp >> tmp >> dst;
    return {src, dst};
  };

  std::vector<std::vector<bool>> graph(52, std::vector<bool>(52));

  int N; std::cin >> N;
  int count{0};
  for (int i{0}; i < N; ++i) {
    auto [src, dst] = parse(std::cin);
    if (src == dst) continue;
    if (graph[encode[src]][encode[dst]]) continue;
    graph[encode[src]][encode[dst]] = true;
    ++count;
  }

  for (int mid{0}; mid < 52; ++mid) {
    for (int src{0}; src < 52; ++src) {
      for (int dst{0}; dst < 52; ++dst) {
        if (src == dst) continue;
        if (graph[src][dst]) continue;
        if (graph[src][mid] && graph[mid][dst]) {
          graph[src][dst] = true;
          ++count;
        }
      }
    }
  }

  std::cout << count << '\n';

  for (int src{0}; src < 52; ++src) {
    for (int dst{0}; dst < 52; ++dst) {
      if (src == dst) continue;
      if (graph[src][dst]) std::cout << decode[src] << " => " << decode[dst] << '\n';
    }
  }
}