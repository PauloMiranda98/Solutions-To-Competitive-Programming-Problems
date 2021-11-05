#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define endl '\n'

using namespace std;

using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};

template <typename flow_t>
struct Dinic{
  struct FlowEdge{
    int from, to, id;
    flow_t cap, flow = 0;
    FlowEdge(int f, int t, flow_t c, int id1) : from(f), to(t), cap(c){
      id = id1;
    }
  };
  const flow_t flow_inf = numeric_limits<flow_t>::max();
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;
  bool bfs(){
    while (!q.empty()){
      int u = q.front();
      q.pop();
      for (int id : adj[u]){
        if (edges[id].cap - edges[id].flow < 1)
          continue;
        if (level[edges[id].to] != -1)
          continue;
        level[edges[id].to] = level[u] + 1;
        q.push(edges[id].to);
      }
    }
    return level[t] != -1;
  }
  flow_t dfs(int u, flow_t pushed){
    if (pushed == 0)
      return 0;
    if (u == t)
      return pushed;
    for (int &cid = ptr[u]; cid < (int)adj[u].size(); cid++){
      int id = adj[u][cid];
      int to = edges[id].to;
      if (level[u] + 1 != level[to] || edges[id].cap - edges[id].flow < 1)
        continue;
      flow_t tr = dfs(to, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }
//Public:
  Dinic(){}
  void init(int _n){
    n = _n;
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  void addEdge(int from, int to, flow_t cap, int id=0){
    assert(n>0);
    edges.emplace_back(from, to, cap, id);
    edges.emplace_back(to, from, 0, -id);
    adj[from].push_back(m);
    adj[to].push_back(m + 1);
    m += 2;
  }
  void resetFlow(){
    for(int i=0; i<m; i++)
      edges[i].flow = 0;
  }
  flow_t maxFlow(int s1, int t1){
    s = s1, t = t1;
    flow_t f = 0;
    while (true){
      level.assign(n, -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      ptr.assign(n, 0);
      while (flow_t pushed = dfs(s, flow_inf))
        f += pushed;
    }
    return f;
  }
};

const int MAXP = 1000000;
int n, m;
int getId(int i, int j){
  return i*(m+1) + j;
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int k, c;
  cin >> n >> m >> k >> c;

  Dinic<int> graph;
  graph.init(n*(m+1) + 2);
  int s = n*(m+1), t = n*(m+1) + 1;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      int p;
      cin >> p;
      graph.addEdge(getId(i, j), getId(i, j+1), MAXP - p);
    }
    graph.addEdge(s, getId(i, 0), INF);
    graph.addEdge(getId(i, m), t, INF);
  }

  while(k--){
    int a, b;
    cin >> a >> b;
    a--; b--;
    for(int j=0; j<m; j++){
      graph.addEdge(getId(a, j), getId(b, j), c);
      graph.addEdge(getId(b, j), getId(a, j), c);
    }
  }

  int total = graph.maxFlow(s, t);
  cout << n*MAXP - total << endl;
  return 0;
}
