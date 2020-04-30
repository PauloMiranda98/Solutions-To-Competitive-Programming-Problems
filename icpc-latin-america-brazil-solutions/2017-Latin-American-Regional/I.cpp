#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

#define MAXN 200010
#define MAXM 200010

struct UnionFind{	
	int n, anc[MAXN], w[MAXN], sz[MAXN];

	UnionFind(){
		for(int i=1; i<MAXN; i++){
			anc[i] = i;
			w[i] = 1;
			sz[i] = 1;
		}		
	}

	//find: O(1)
	int find(int x){    
		if(anc[x] == x)
			return x;		
		return anc[x] = find(anc[x]);
	}

	//isSame: O(1) 
	bool isSame(int x, int y){
		return find(x) == find(y);
	}

	//join: O(1) 
	void join(int x, int y){    
		x = find(x);
		y = find(y);
		
		if(x == y)
			return;
		
		if(w[x] < w[y]){
			anc[x] = y;
			sz[y] += sz[x];
		}else if(w[x] > w[y]){
			anc[y] = x;
			sz[x] += sz[y];
		}else{        
			anc[x] = y;
			sz[y] += sz[x];
			
			w[y]++;
		}
	}
	
	int size(int x){
		return sz[find(x)];
	}
};

int n, m;

typedef long long ll;
typedef tuple<ll, int, int> tp;

tp edgeList[MAXM];
typedef pair<int, ll> pil;
vector<pil> adjList[MAXN];

ll kruskal() {
	ll cost = 0;
	UnionFind uf;
	
	sort(edgeList, edgeList + m);
	
	for(int i = 0; i < m; i++) {
		int u, v; ll c;
		tie(c, u, v) = edgeList[i];
		
		if(!uf.isSame(u, v ) ) { 
			cost += c;
			uf.join(u, v);
			adjList[u].push_back(pil(v, c));
			adjList[v].push_back(pil(u, c));
		}
	}
	
	return cost;
}

const int INF = 0x3f3f3f3f;

namespace n_lca{
	const int MAXLOGN = 20;
	typedef ll lca_t;
	typedef pair<int, lca_t> lca_p;

	const lca_t neutral = -INF;

	int level[MAXN], n;
	int P[MAXN][MAXLOGN];
	lca_t D[MAXN][MAXLOGN];

	lca_t join(lca_t a, lca_t b){
		return max(a, b);
	}
	void dfs(int u) {
		for(int i=0; i < (int)adjList[u].size(); i++) {
			int v = adjList[u][i].first;
			ll w = adjList[u][i].second;
			
			if(v == P[u][0]) continue;
			P[v][0] = u; D[v][0] = w;
			level[v] = 1 + level[u];
			dfs(v);
		}
	}

	void build(int root, int _n) {
		n = _n;
		level[root] = 0;
		P[root][0] = root; D[root][0] = neutral;
		dfs(root);
		for(int j = 1; j < MAXLOGN; j++)
			for(int i = 1; i <= n; i++) {
				P[i][j] = P[P[i][j-1]][j-1];
				D[i][j] = join(D[P[i][j-1]][j-1], D[i][j-1]);
			}
	}

	lca_p lca(int u, int v) {
		if (level[u] > level[v]) swap(u, v);
		int d = level[v] - level[u];
		lca_t ans = neutral;
		for(int i = 0; i < MAXLOGN; i++) {
			if (d & (1<<i)) {
				ans = join(ans, D[v][i]);
				v = P[v][i];
			}
		}	
		if (u == v) return lca_p(u, ans);
		for(int i = MAXLOGN-1; i >= 0; i--){
			while(P[u][i] != P[v][i]) {
				ans = join(ans, D[v][i]);
				ans = join(ans, D[u][i]);
				u = P[u][i]; v = P[v][i];
			}
		}
		ans = join(ans, D[v][0]);
		ans = join(ans, D[u][0]);
		
		return lca_p(P[u][0], ans);
	}
};
typedef pair<int, int> pii;
map<pii, ll> cost;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	
	for(int i=0; i<m; i++){
		int u, v; ll w;
		cin >> u >> v >> w;
		edgeList[i] = tp(w, u, v);
		cost[pii(u, v)] = w;
		cost[pii(v, u)] = w;
	}	
	ll ans = kruskal();
	
	n_lca::build(1, n);
	int q;
	cin >> q;
	while(q--){
		int a, b;
		cin >> a >> b;
		cout << ans + cost[pii(a, b)] - n_lca::lca(a, b).second << endl;
	}
	return 0;
}
