#include <iostream>

int N;
int arr[1'000'001];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;
  for (int i{1}; i <= N; ++i) std::cin >> arr[i];

  int left{1}, right{N};
  int ans{0};
  while (left <= right) {
    if (arr[left] == arr[right]) {
      ++left;
      --right;
      continue;
    }
    ++ans;
    if (arr[left] < arr[right]) {
      arr[left + 1] += arr[left];
      ++left;
    }
    else {
      arr[right - 1] += arr[right];
      --right;
    }
  }

  std::cout << ans;
}