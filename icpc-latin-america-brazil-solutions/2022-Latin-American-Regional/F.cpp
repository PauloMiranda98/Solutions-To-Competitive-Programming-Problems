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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());
namespace Kuhn{
  int na, nb;
  vector<vector<int>> adj;
  vector<int> vis, ma, mb;
  void init(int na1, int nb1){
    na = na1, nb = nb1;
    adj.assign(na, vector<int>());
    vis.assign(na + nb, 0);
    ma.assign(na, -1);
    mb.assign(nb, -1);
  }
  void addEdge(int a, int b) { 
    adj[a].push_back(b); 
  }
  bool dfs(int u) {
    vis[u] = 1;
    for (int to : adj[u]){
      if(vis[na+to]) 
        continue;
      vis[na+to] = 1;
      if (mb[to] == -1 or dfs(mb[to])) {
        ma[u] = to, mb[to] = u;
        return true;
      }
    }
    return false;
  }
  int matching() {
    int ans = 0, c = 1;
    for (auto& v: adj) 
      shuffle(v.begin(), v.end(), rng);
    while (c) {
      for (int j = 0; j < nb; j++) 
        vis[na+j] = 0;
      c = 0;
      for (int i = 0; i < na; i++)
        if (ma[i] == -1 and dfs(i))
          ans++, c = 1;
    }
    return ans;
  }
  pair<vector<int>, vector<int>> minimumVertexCover() {
    matching();
    for (int i = 0; i < na+nb; i++) 
      vis[i] = 0;
    for (int i = 0; i < na; i++) 
      if (ma[i] == -1) 
        dfs(i);
    vector<int> va, vb;
    for (int i = 0; i < na; i++) 
      if (!vis[i]) 
        va.push_back(i);
    for (int i = 0; i < nb; i++) 
      if (vis[na+i]) 
        vb.push_back(i);
    return {va, vb};
  }
  vector<int> maximumAntichain(){
    auto [l, r] = minimumVertexCover();
    set<int> L(l.begin(), l.end());
    set<int> R(r.begin(), r.end());
    vector<int> ans;
    for (int i = 0; i < na; i++)
      if (!L.count(i) and !R.count(i))
        ans.push_back(i);
    return ans;
  }

  vector<vector<int>> minimumNumberChains(){
    matching();
    vector<vector<int>> chains;
    for(int i=0; i<na; i++) if(mb[i] == -1){
      vector<int> path;
      for(int x=i; x != -1; x=ma[x])
        path.push_back(x);
      chains.push_back(path);
    }
    return chains;
  }
};

const int MAXN = 101;
int dp[MAXN][MAXN];
vector<int> adj[2][MAXN];

bool solve(int a, int dadA, int b, int dadB){
  if(dp[a][b] != -1)
    return dp[a][b];

  vector<pii> edges;
  
  int idA = 0;
  for(int toA: adj[0][a]) if(toA != dadA){
    int idB = 0;
    for(int toB: adj[1][b]) if(toB != dadB){
      if(solve(toA, a, toB, b))
        edges.emplace_back(idA, idB);
      idB++;
    }
    idA++;
  }

  int mx = (int)adj[1][b].size() - (dadB != -1);
  Kuhn::init(adj[0][a].size(), adj[1][b].size());
  
  for(auto [i, j]: edges){
    Kuhn::addEdge(i, j);
  }
  
  dp[a][b] = (Kuhn::matching() == mx);

  return dp[a][b];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n[2];
  
  for(int i=0; i<2; i++){
    cin >> n[i];
    
    for(int j=0; j<n[i]-1; j++){
      int a, b;
      cin >> a >> b;
      a--; b--;
      
      adj[i][a].push_back(b);
      adj[i][b].push_back(a);
    }
  }

  for(int i=0; i<n[0]; i++){
    memset(dp, -1, sizeof(dp));
    if(solve(i, -1,  0, -1)){
      cout << "Y" << endl;
      return 0;
    }
  }
  
  cout << "N" << endl;
  
  return 0;
}
