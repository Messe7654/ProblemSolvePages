#include <algorithm>
#include <iostream>

int numbers[1'000'001];

int partition(int left, int right, int pivot) {
  while (left <= right) {
    while (numbers[left] < pivot) ++left;
    while (numbers[right] >= pivot) --right;
    std::swap(numbers[left], numbers[right]);
  }
  return left;
}

void sort(int left, int right) {
  if (l >= r) return;
  

}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  for (int i{1}; i <= N; i++) std::cin >> numbers[i];
  


  for (int i{1}; i <= N; i++) std::cout << numbers[i] << '\n';
}