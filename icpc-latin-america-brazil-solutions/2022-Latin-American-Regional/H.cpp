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

const int MAXN = 301;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n;
  cin >> n;

  map<string, int> mpId;
  vector<string> vs(n);
  for(int i=0; i<n; i++){
    string s;
    cin >> s;

    vs[i] = s;
    mpId[s] = i;
  }
  
  int r;
  cin >> r;
  
  vector<bitset<MAXN>> pos(n);
  
  for(int i=0; i<n; i++)
    pos[i].set();
  
  for(int i=0; i<r; i++){
    int m, w;
    cin >> m >> w;
    w--;
    
    bitset<MAXN> aux;
    while(m--){
      string s;
      cin >> s;
      
      int id = mpId[s];
      
      aux[id] = 1;
      for(int p=0; p<w; p++)
        pos[p][id] = 0;
    }
    
    pos[w] = pos[w] & aux;
  }
  
  Kuhn::init(n, n);
  
  for(int p=0; p<n; p++){
    for(int id=0; id<n; id++){
      if(pos[p][id])
        Kuhn::addEdge(p, id);
    }
  }
  
  assert(Kuhn::matching() == n);
  
  for(int i=0; i<n; i++){
    cout << vs[Kuhn::ma[i]] << " ";
  }
  
  
  
  cout << endl;
  
  return 0;
}
