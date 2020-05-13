#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 200010;
vector<pli> adj[MAXN];
int n, m;
ll dist[MAXN];
int dad[MAXN];
void Dijkstra(int s){	
	for(int i=0; i<=n; i++){
		dist[i] = INFLL;	
		dad[i] = -1;
	}	
	dist[s] = 0;
	priority_queue< pli, vector<pli>, greater<pli> > st;	
	st.push(pli(dist[s], s));	
	while(!st.empty()){
		ll w = st.top().first;
		int u = st.top().second;
		st.pop();
		if(w > dist[u]) continue;
		for(pli p: adj[u]){
			ll edge = p.first;  
			int to = p.second;
			if(w+edge < dist[to]){
				dist[to] = w + edge;
				dad[to] = u;
				st.push(pli(dist[to], to));
			}
		}
	}
}

typedef pair<ll, int> pii;
set<pii> st;
bool used[MAXN];
int dad2[MAXN];
void dfs(int u, int p){
	if(used[u] or st.count(pii(p, u)))
		return;	
	dad2[u] = p;
	used[u] = true;
	for(auto to: adj[u])
		dfs(to.second, u);	
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	
	for(int i=0; i<m; i++){
		int a, b; ll w;
		cin >> a >> b >> w;
		adj[a].push_back(pli(w, b));
		adj[b].push_back(pli(w, a));
	}
	//Find the edges that are in the Dijkstra Tree
	Dijkstra(1);
	//Insert into a set of forbidden Edges
	for(int i=0; i<n; i++){
		st.insert(pii(i, dad[i]));	
	}
	//Find Path without forbidden edges
	for(int i=0; i<n; i++)
		dad2[i] = -2;
	dfs(0, -1);
	if(dad2[1] == -2){
		cout << "impossible" << endl;
		return 0;		
	}
	//Recover answer
	vector<int> ans;
	int p = 1;
	while(p != -1){
		ans.push_back(p);
		p = dad2[p];
	}
	reverse(ans.begin(), ans.end());
	cout << ans.size();
	for(int x: ans)
		cout << " " << x;
	cout << endl;
	return 0;
}
