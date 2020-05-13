#include <bits/stdc++.h>

#define x first
#define y second
#define EB emplace_back
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using pii = pair<int, int>;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;

template <typename flow_t>
struct Dinic{
  struct FlowEdge{
    int v, u;
    flow_t cap, flow = 0;
    FlowEdge(int v, int u, flow_t cap) : v(v), u(u), cap(cap) {}
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
      int v = q.front();
      q.pop();
      for (int id : adj[v]){
        if (edges[id].cap - edges[id].flow < 1)
          continue;
        if (level[edges[id].u] != -1)
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }
  flow_t dfs(int v, flow_t pushed){
    if (pushed == 0)
      return 0;
    if (v == t)
      return pushed;
    for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++){
      int id = adj[v][cid];
      int u = edges[id].u;
      if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
        continue;
      flow_t tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }
  Dinic(){}
  void init(int _n){
    n = _n;  
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  void addEdge(int v, int u, flow_t cap){
    assert(n>0);
    edges.push_back(FlowEdge(v, u, cap));
    edges.push_back(FlowEdge(u, v, 0));
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }
  flow_t maxFlow(int s1, int t1){
    s = s1, t = t1;
    flow_t f = 0;
    for(int i=0; i<m; i++)
      edges[i].flow = 0;
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
pii vb[300], vr[300];
const double EPS = 1e-12;
double dist(pii a, pii b){
	return sqrtl((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
int n, b, r;
int solve(double x){
	Dinic<int> dinic;
	dinic.init(b+r+2);
	for(int i=1; i<=b; i++)
		dinic.addEdge(0, i, 1);
	for(int j=1; j<=r; j++)
		dinic.addEdge(b+j, b+r+1, 1);	
	for(int i=1; i<=b; i++){
		for(int j=1; j<=r; j++){
			if(dist(vb[i], vr[j]) < x+EPS)
				dinic.addEdge(i, b+j, 1);
		}
	}
	//Solve Minimum Vertex Cover using Flow
	int mvc = dinic.maxFlow(0, b+r+1);
	//Solve Maximum Independent Set
	int mis = (b+r)-mvc;
	return mis;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> b >> r;
	for(int i=1; i<=b; i++)
		cin >> vb[i].x >> vb[i].y;
	for(int i=1; i<=r; i++)
		cin >> vr[i].x >> vr[i].y;
	double lo=0, hi = 1e18, ans=1e18;
	while(abs(hi-lo)>EPS){
		double mid = (lo+hi)/2;
		if(solve(mid) >= n){
			lo = mid;
			ans = mid;
		}else{
			hi = mid;
		}
	}
	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}
