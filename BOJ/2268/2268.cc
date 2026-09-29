#include <iostream>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(int size);
  long long Query(int left, int right);
  void Update(int index, int value);

 private:
  int size_;
  std::vector<long long> tree_;
};

SegmentTree::SegmentTree(int size) {
  size_ = 1;
  while (size_ < size) size_ <<= 1;
  tree_.resize(size_ << 1);
}

void SegmentTree::Update(int index, int value) {
  index |= size_; tree_[index] = value;
  while (index >>= 1) {
    tree_[index] = tree_[index << 1] + tree_[index << 1 | 1];
  }
}

long long SegmentTree::Query(int left, int right) {
  left |= size_; right |= size_;
  long long ret{0};
  while (left <= right) {
    if (left & 1) ret += tree_[left++];
    if (~right & 1) ret += tree_[right--];
    left >>= 1; right >>= 1;
  }
  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;
  SegmentTree seg(N);

  for (int i{0}; i < M; i++) {
    int op, a, b;
    std::cin >> op >> a >> b;
    if (1 == op) { // Modify
      seg.Update(a, b);
    }
    else { // Sum
      if (a > b) std::swap(a, b);
      std::cout << seg.Query(a, b) << '\n';
    }
  }
}