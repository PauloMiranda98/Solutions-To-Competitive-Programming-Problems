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

const int MAXN = 10010;

int cycle[MAXN];
int seen[MAXN];
int aux[MAXN];
vector<int> active;
vector<pii> adj[MAXN];

void buildCycle(int sum, int last){
  int i = (int)active.size()-1;
  while(i >= 0){
    cycle[active[i]] = sum;
    if(active[i] == last)
      break;
    i--;
  }
}
void dfs(int u, int p=-1, int sum=0){
  seen[u] = 1;
  aux[u] = sum;
  active.push_back(u);
  for(auto [to, w]: adj[u]){
    if(to == p) 
      continue;
    if(seen[to] == 1)
      buildCycle(sum - aux[to] + w, to);
    else if(seen[to] == 0)
      dfs(to, u, sum + w);
  }
  seen[u] = 2;
  active.pop_back();
}

int dist[MAXN], n;
int solve(int s, int sz){
  int ans = INF;
  for(int i=1; i<=n; i++)
    dist[i] = INF;
  dist[s] = 0;
  priority_queue<pii, vector<pii>, greater<pii>> st;
  st.push(pii(dist[s], s)); 
  while(!st.empty()){
    auto [d, u] = st.top();
    st.pop();
    if(d > dist[u]) continue;

    if(cycle[u] >= sz)
      ans = min(ans, cycle[u] + 2*dist[u]);

    for(auto [to, w]: adj[u]){
      if(d+w < dist[to]){
        dist[to] = d + w;
        st.push(pii(dist[to], to));
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int m;
  cin >> n >> m;
  for(int i=0; i<m; i++){
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back(pii(b, c));
    adj[b].push_back(pii(a, c));
  }
  for(int i=1; i<=n; i++){
    if(seen[i] == 0)
      dfs(i);
  }
  int q;
  cin >> q;
  while(q--){
    int u, sz;
    cin >> u >> sz;
    int ans = solve(u, sz);
    if(ans == INF)
      cout << -1 << endl;
    else
      cout << ans << endl;
  }
  return 0;
}
