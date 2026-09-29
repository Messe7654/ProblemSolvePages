#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int P; std::cin >> P;
  
  for (int dataset{1}; dataset <= P; ++dataset) {
    int B, M; std::cin >> B >> M;
    std::vector<std::vector<std::vector<int>>> DP(B + 1, std::vector<std::vector<int>>(M + 1, std::vector<int>(M + 1)));
    
  }
  //
}