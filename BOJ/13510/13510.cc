#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int N;

std::vector<int> edge_weight;

std::vector<int> segment_tree;
std::vector<int> head;
std::vector<int> chain;
std::vector<int> chain_size;
std::vector<int> depth;
std::vector<int> parent;
std::vector<int> weight;
std::vector<int> discover;

std::vector<int> src;
std::vector<int> dst;

std::vector<std::vector<std::pair<int, int>>> graph;

void DFS() {
  std::vector<bool> visited(N + 1, false);
  int order{0};
  std::function<void(int)> _imple_;
  _imple_ = [&](int now) -> void {
    weight[now] = 1;
    visited[now] = true;
    for (auto [next, cost] : graph[now]) {
      if (visited[next] != true) {
        depth[next] = depth[now] + 1;
        parent[next] = now;
        _imple_(next);
        weight[now] += weight[next];
      }
    }
  };

  _imple_(0);
}

void HLD() {
  for (auto& adjacency_list : graph) {
    std::sort(adjacency_list.begin(), adjacency_list.end(), 
              [](const auto& lhs, const auto& rhs) {
                return weight[lhs.first] > weight[rhs.first]; });
  }

  std::vector<bool> visited(N + 1);
  int order1{0}, order2{0};

  std::function<void(int)> _imple_;
  _imple_ = [&](int now) -> void {
    visited[now] = true;

    for (auto [next, cost] : graph[now]) {
      if (visited[next] == true) continue;
      chain[next] = chain[now];
      discover[next] = ++order1;
      _imple_(next);
      break;
    }

    for (auto [next, cost] : graph[now]) {
      if (visited[next] == true) continue;
      chain[next] = ++order2;
      head[order2] = next;
      discover[next] = ++order1;
      _imple_(next);
    }
  };

  _imple_(0);
  for (int i{0}; i < N; ++i) {
    ++chain_size[chain[i]];
  }
}

void update(int Tidx, int start, int end, int Aidx, int val) {
  if (Aidx < start || end < Aidx) return;
  if (start == end) {
    segment_tree[Tidx] = val;
    return;
  }
  int mid = start + ((end - start) >> 1);
  update(Tidx << 1, start, mid, Aidx, val);
  update(Tidx << 1 | 1, mid + 1, end, Aidx, val);
  segment_tree[Tidx] = std::max(segment_tree[Tidx << 1], segment_tree[Tidx << 1 | 1]);
}

int get(int Tidx, int start, int end, int left, int right) {
  if (right < start || end < left) {
    return 0;
  }

  if (left <= start && end <= right) {
    return segment_tree[Tidx];
  }

  int mid = start + ((end - start) >> 1);
  return std::max(get(Tidx << 1, start, mid, left, right), get(Tidx << 1 | 1, mid + 1, end, left, right));
}

void query1(int i, int c) {
  if (depth[src[i]] > depth[dst[i]]) std::swap(src[i], dst[i]);
  update(1, 0, N - 1, discover[dst[i]], c);
};

int query2(int u, int v) {
  if (u == v) return 0;
  int ret = 0;
  while (chain[u] != chain[v]) {
    if (depth[head[chain[u]]] < depth[head[chain[v]]]) std::swap(u, v);
    int start = head[chain[u]];
    ret = std::max(ret, get(1, 0, N - 1, discover[start], discover[u]));
    u = parent[start];
  }

  if (depth[u] > depth[v]) std::swap(u, v);
  ret = std::max(ret, get(1, 0, N - 1, discover[u] + 1, discover[v]));
  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;

  edge_weight.resize(N + 1);

  segment_tree.resize(N << 2);
  head.resize(N + 1);
  chain.resize(N + 1);
  chain_size.resize(N + 1);
  depth.resize(N + 1);
  parent.resize(N + 1);
  discover.resize(N + 1);
  weight.resize(N + 1);
  graph.resize(N + 1);
  src.resize(N + 1);
  dst.resize(N + 1);

  for (int i{1}; i < N; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u; --v;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
    src[i] = u;
    dst[i] = v;
    edge_weight[i] = w;
  }

  DFS();
  HLD();
  #ifndef ONLINE_JUDGE
  auto println = [](std::string_view rem, const auto& list) {
    if (list.empty()) std::cout << rem << "[]\n";
    else {
      std::cout << rem << "[";
      int size = static_cast<int>(list.size());
      for (int i{0}; i < size; ++i) {
        std::cout << list[i] << ((i + 1 == size) ? "]\n" : ", ");
      }
    }
  };

  println("discover : ", discover);
  println("chain : ", chain);
  println("chain_size : ", chain_size);
  println("weight : ", weight);
  println("head : ", head);
  println("depth : ", depth);
  #endif

  for (int i{1}; i < N; ++i) query1(i, edge_weight[i]);

  int M; std::cin >> M;
  for (int i{0}; i < M; ++i) {
    int op, a, b;
    std::cin >> op >> a >> b;
    if (op == 1) {
      query1(a, b);
    }
    else {
      --a; --b;
      std::cout << query2(a, b) << '\n';
    }
  }

}