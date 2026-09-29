#include <algorithm>
#include <iostream>
#include <vector>

void print(std::vector<int>& vector) {
  if (vector.empty()) {
    std::cout << "[]\n";
    return;
  }
  int size = static_cast<int>(vector.size());
  std::cout << "[";
  for (int i{0}; i < size; i++) {
    std::cout << vector[i] << ((i == size - 1) ? "]\n" : ", ");
  }
}

std::vector<int>& round(std::vector<int>& vector, std::vector<int>& origin_indices) {
  int size = static_cast<int>(vector.size());
  std::vector<int> rank(size);
  for (int i{0}; i < size; i++) rank[i] = i;
  for (int i{0}; i < size - 1; i++) {
    if (vector[i] > vector[i + 1]) {
      std::swap(vector[i], vector[i + 1]);
      std::swap(rank[i], rank[i + 1]);
      std::swap(origin_indices[i], origin_indices[i + 1]);
      // std::cout << "vector[" << i << "], vector[" << i + 1 << "] swaped ";
      // print(vector);
    }
  }
  std::cout << "rank : ";
  for (int i{0}; i < size; i++) rank[i] = i - rank[i];
  print(rank);
  std::cout << "o_idx: ";
  print(origin_indices);
  return vector;
}

int main() {
  std::vector<int> sample, origin_indices;
  int size;
  std::cin >> size;
  sample.resize(size);
  origin_indices.resize(size);
  for (int i{0}; i < size; i++) {
    std::cin >> sample[i];
    origin_indices[i] = i;
  }
  std::cout << "Round 0\n";
  std::cout << "o_idx: "; print(origin_indices);
  std::cout << "value: "; print(sample);
  for (int i{0}; i < size; i++) {
    std::cout << "Round " << i + 1 << '\n';
    round(sample, origin_indices);
    std::cout << "value :"; print(sample);
  }
}