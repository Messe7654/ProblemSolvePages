#include <iostream>
#include <vector>

int N;
int A[1'000'001];

struct group {
  int value;
  int count;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;
  for (int i{1}; i <= N; ++i) std::cin >> A[i];

  std::vector<group> stack;
  stack.push_back({A[1], 1});
  for (int i{2}; i <= N; ++i) {
    if (A[i] < stack.back().value) {
      stack.push_back({A[i], 1});
    }
    else if (A[i] == stack.back().value) {
      ++stack.back().count;
    }
    else {
      while (stack.empty() != true && stack.back().value < A[i]) {
        
      }
    }
  }
}