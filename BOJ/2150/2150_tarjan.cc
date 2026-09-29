#include <algorithm>
#include <iostream>
#include <vector>

int V, E;
std::vector<int> adj[10'001];
int discover[10'001];
int finished[10'001];


std::vector<int> tarjan() {
  int euler_counter{0};
  auto DFS = [&](int start) {
    if (discover[start] != 0) return;
    discover[start] = ++euler_counter;
    std::vector<int> stack;
    stack.push_back(start);

    while (stack.empty() != true) {
      auto now = stack.back();
      if (discover[now] == 0) {
        discover[now] = ++euler_counter;
        for (auto rit{adj[now].rbegin()}; rit != adj[now].rend(); ++rit) {
          
        }
      }
    }
    
  };
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> V >> E;

  for (int i{0}; i < E; ++i) {
    int A, B;
    std::cin >> A >> B;
    adj[A].push_back(B);
  }


}