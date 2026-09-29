#include <iostream>
#include <stack>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::stack<std::pair<int, int>> stack; // stack := {height, index}에 대한 stack
  stack.push({100'000'001, 0});
  for (int i{1}; i <= N; i++) {
    int height; std::cin >> height;
    while(stack.empty() != true && stack.top().first < height) {
      stack.pop();
    }
    std::cout << stack.top().second << ' ';
    stack.push({height, i});
  }
}