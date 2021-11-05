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
const int MAXN = 100010;
vector<int> adj[MAXN];
int pos[MAXN];
int node[MAXN];
int p;
void dfs(int u){
  pos[u] = p++;
  node[pos[u]] = u;
  for(int to: adj[u])
    dfs(to);
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int q;
  cin >> q;
  vector<pii> v(q);
  for(int i=0; i<q; i++){
    int t, x;
    cin >> t >> x;
    v[i] = pii(t, x);
  }
  int id = 1;
  for(auto [t, x]: v){
    if(t == 1){
      adj[x].push_back(++id);
    }
  }
  dfs(1);

  id = 1;
  set<int> st;
  int last = 1;
  for(auto [t, x]: v){
    if(t == 1){
      st.insert(pos[++id]);
    }else{
      st.erase(pos[x]);
      if(x == last){
        int mn = *st.begin();
        last = node[mn];
      }
      cout << last << endl;
    }
  }
  return 0;
}
