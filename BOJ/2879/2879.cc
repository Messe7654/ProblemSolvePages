#include <iostream>
#include <vector>

auto println = [](const auto& rem, const auto& list) -> void {
  if (list.empty()) { std::cout << rem << '\n'; return; }
  std::cout << rem;
  for (std::size_t i{0}; i < list.size(); ++i) {
    std::cout << list[i] << ((i + 1 == list.size()) ? '\n' : ' ');
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N;
  std::cin >> N;
  std::vector<int> a(N);
  for (int i{0}; i < N; ++i) { 
    std::cin >> a[i];
  }
  for (int i{0}; i < N; ++i) {
    int x;
    std::cin >> x;
    a[i] -= x;
  }

  println("a : ", a);
}