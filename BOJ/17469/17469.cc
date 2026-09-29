#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, Q;
  std::cin >> N >> Q;
  std::vector<int> parent(N);
  std::vector<int> color(N);

  for (int i{1}; i < N; ++i) {
    std::cin >> parent[i];
    --parent[i];
  }

  for (int i{0}; i < N; ++i) std::cin >> color[i];

  std::vector<std::pair<std::string, int>> queries(N + Q - 1);
  for (int i{0}; i < N + Q - 1; ++i) 
  
  // read N + Q - 1 lines to queries's text
  // reverse queries

  // process queries sequentially

  // query type 1: (1 a)
  //   Union the set of colors between a and parent[a]
  //   if |set_a| > |set_{parent[a]}| then swap them and merge into set_{parent[a]}
  //   otherwise, simply merge into set_{parent[a]}
  // query type 2: (2 a)
  //   Find the vertex a, and answer_of_query is |set_a|
  //   I think we manage the representive value of the set's which is the root of the subtree
}