#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;

class SegTreeLazy{
private:
	typedef pii Node;
	vector<Node> st;
	vector<int> lazy;
	vector<int> v;
	int n;
	Node neutral = pii(INF, 0);
	inline Node join(Node a, Node b){
		return min(a, b);
	}
	inline void upLazy(int &node, int &i, int &j){
		if (lazy[node] != 0){
			st[node].F += lazy[node];
			if (i != j){
				lazy[(node << 1)] += lazy[node];
				lazy[(node << 1) + 1] += lazy[node];
			}
			lazy[node] = 0;
		}
	}
	void build(int node, int i, int j){
		if (i == j){
			st[node] = pii(v[i], i);
			return;
		}
		int m = (i + j) / 2;
		int l = (node << 1);
		int r = l + 1;
		build(l, i, m);
		build(r, m + 1, j);
		st[node] = join(st[l], st[r]);
	}
	Node query(int node, int i, int j, int a, int b){
		upLazy(node, i, j);
		if ((i > b) or (j < a))
			return neutral;
		if ((a <= i) and (j <= b)){
			return st[node];
		}
		int m = (i + j) / 2;
		int l = (node << 1);
		int r = l + 1;
		return join(query(l, i, m, a, b), query(r, m + 1, j, a, b));
	}
	void update(int node, int i, int j, int a, int b, int value){
		upLazy(node, i, j);
		if ((i > j) or (i > b) or (j < a))
			return;
		if ((a <= i) and (j <= b)){
			lazy[node] = value;
			upLazy(node, i, j);
		}else{
			int m = (i + j) / 2;
			int l = (node << 1);
			int r = l + 1;
			update(l, i, m, a, b, value);
			update(r, m + 1, j, a, b, value);
			st[node] = join(st[l], st[r]);
		}
	}
public:
	template <class MyIterator>
	SegTreeLazy(MyIterator begin, MyIterator end){
		n = end - begin;
		v = vector<int>(begin, end);
		st.resize(4 * n + 5);
		lazy.assign(4 * n + 5, 0);
		build(1, 0, n - 1);
	}
	//0-indexed [a, b]
	Node query(int a, int b){
		return query(1, 0, n - 1, a, b);
	}
	//0-indexed [a, b]
	void update(int a, int b, int value){
		update(1, 0, n - 1, a, b, value);
	}
};

const int MOD = 1000000007;
const int MAXN = 100010;

vector<int> adj[MAXN];
int n, m, A, B;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m >> A >> B;
		
	for(int i=0; i<m; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> va(n), vb(n);
	for(int i=0; i<n; i++){
		va[i] = adj[i].size();
		vb[i] = n-adj[i].size()-1;
	}

	SegTreeLazy stA(all(va)), stB(all(vb));
	int ans = n;
	while(stA.query(0, n-1).F < A or stB.query(0, n-1).F < B){
		pii p;
		p = stA.query(0, n-1);
		if(p.F < A){
			stB.update(0, n-1, -1);
			for(int to: adj[p.S]){
				stA.update(to, to, -1);			
				stB.update(to, to, +1);			
			}
			stA.update(p.S, p.S, INF);
			stB.update(p.S, p.S, INF);
			ans--;
		}
		p = stB.query(0, n-1);
		if(p.F < B){
			stB.update(0, n-1, -1);
			for(int to: adj[p.S]){
				stA.update(to, to, -1);			
				stB.update(to, to, +1);			
			}
			stA.update(p.S, p.S, INF);
			stB.update(p.S, p.S, INF);
			ans--;
		}		
	}
	
	cout << ans << endl;
	return 0;
}
