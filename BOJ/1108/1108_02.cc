#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

#define debug(rem) \
  if constexpr (local) std::cout << rem

#ifdef DEBUG
constexpr bool local = true;
#else
constexpr bool local = false;
#endif

long long N;
std::vector<std::vector<long long>> adj(1);
std::unordered_map<std::string, long long> dict;
std::vector<long long> leader(1);

std::unordered_map<long long, std::unordered_set<long long>> scc_adj;

/// @brief string을 입력받아, dict에 해당하는 index를 반환하는 함수
/// @param str 입력할 string
/// @return  dict[str], 입력된 str들은 [1..size()]에 매핑되어 있음
long long GetIdx(std::string str) {
  static long long idx{1};
  if (dict.find(str) == dict.end()) {
    dict.insert({str, idx++});
    adj.push_back(std::vector<long long>());
    leader.push_back(0);
  }
  return dict[str];
}

void tarjan() {
  long long euler_tour_counter{0};
  std::vector<bool> visit(dict.size() + 1, false);
  std::vector<long long> discover(dict.size() + 1, 0);
  std::vector<long long> low_link(dict.size() + 1, 0);
  std::vector<long long> stack;
  std::vector<std::vector<long long>> SCCs;

  std::function<void(long long)> dfs;
  dfs = [&](long long now) -> void {
    debug("DEBUG> dfs(") << now << ") called\n";
    visit[now] = true;
    discover[now] = ++euler_tour_counter;
    low_link[now] = euler_tour_counter;

    stack.push_back(now);

    for (auto next : adj[now]) {
      if (discover[next] == 0) {
        dfs(next);
        low_link[now] = std::min(low_link[now], low_link[next]);
      }
      else if (visit[next] == true) {
        low_link[now] = std::min(low_link[now], discover[next]);
      }
    }

    if (low_link[now] == discover[now]) {
      std::vector<long long> SCC;
      while (stack.empty() != true) {
        long long top = stack.back();
        stack.pop_back();

        SCC.push_back(top);
        visit[top] = false;
        if (now == top) break;
      }
      for (auto member : SCC) {
        leader[member] = now;
      }
      SCCs.push_back(SCC);
    }
  };

  for (long long i{1}; i <= dict.size(); ++i) {
    if (discover[i] == 0) dfs(i);
  }

  for (auto SCC : SCCs) {
    debug("DEBUG> SCC : [");
    for (auto member : SCC) {
      debug(" ") << member;
      for (auto adjacent_vertex : adj[member]) {
        if (leader[member] == leader[adjacent_vertex]) continue;
        scc_adj[leader[member]].insert(leader[adjacent_vertex]);
      }
    }
    debug(" ]\n");
  }
};



int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  // INPUT
  std::cin >> N;

  for (int i{1}; i <= N; ++i) {
    std::string src, dst;
    int count;
    std::cin >> src >> count;
    long long src_id = GetIdx(src);
    for (int j{0}; j < count; ++j) {
      std::cin >> dst;
      long long dst_id = GetIdx(dst);
      adj[src_id].push_back(dst_id);
    }
  }

  std::string S;
  std::cin >> S;
  // Get SCCs
  tarjan();

  // topological sort
  std::function<long long(long long)> func;
  std::vector<long long> visited(dict.size() + 1, 1);
  func = [&](long long start) -> long long {
    long long ret{1};
    for (auto next : scc_adj[start]) {
      if (visited[next] != 1) ret += visited[next];
      else ret += func(next);
    }
    return visited[start] = ret;
  };

  std::cout << func(GetIdx(S));
}