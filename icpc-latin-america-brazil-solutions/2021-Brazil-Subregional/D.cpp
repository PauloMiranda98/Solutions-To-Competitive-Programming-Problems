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

typedef pair<int, int> pii;
const int N = 500010;
pii parent[N];
int rk[N];
int bipartite[N];

void make_set(int v) {
  parent[v] = pii(v, 0);
  rk[v] = 0;
  bipartite[v] = true;
}

pii find_set(int v) {
  if (v != parent[v].first) {
    int parity = parent[v].second;
    parent[v] = find_set(parent[v].first);
    parent[v].second ^= parity;
  }
  return parent[v];
}

void add_edge(int a, int b) {
  int x, y;
  tie(a, x) = find_set(a);
  tie(b, y) = find_set(b);
  if (a == b) {
    if (x == y)
      bipartite[a] = false;
  }else{
    if (rk[a] < rk[b])
      swap (a, b);
    parent[b] = pii(a, x^y^1);
    bipartite[a] &= bipartite[b];
    if (rk[a] == rk[b])
      ++rk[a];
  }
}

bool is_bipartite(int v) {
  return bipartite[find_set(v).first];
}

bool solve(vector<pii> v){
  int k = v.size();
  map<int, int> f1;
  map<pii, int> f2;
  for(auto p: v){
    if(p.F == p.S){
      f1[p.F]++;
    }else{
      f1[p.F]++;
      f1[p.S]++;
    }
    f2[p]++;
  }
  for(auto p: v){
    int t = f1[p.F] + f1[p.S] - f2[p];

    if(t < k)
      return true;
  }

  return false;
}

typedef tuple<int, int, int> tp;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<tp> v(m);
  for(int i=1; i<=n; i++)
    make_set(i);

  for(int i=0; i<m; i++){
    int x, y, w;
    cin >> x >> y >> w;
    v[i] = tp(w, x, y);
  }
  sort(all(v), greater<tp>());

  vector<int> ans;

  bool b = true;
  for(int i=0; i<m and b; ){
    auto [w0, x0, y0] = v[i];
    int j = i;

    vector<pii> aux;
    while(j < m){
      auto [w1, x1, y1] = v[j];
      if(w0 != w1)
        break;
      auto [x, px] = find_set(x1);
      auto [y, py] = find_set(y1);
      int A = 2*x + px;
      int B = 2*y + py;

      if(A/2 != B/2 or A == B)
        aux.emplace_back(A, B);

      j++;
    }

    for(int k=i; k<j; k++){
      auto [w1, x1, y1] = v[k];
      add_edge(x1, y1);
      b &= is_bipartite(x1);
    }

    if(solve(aux))
      ans.push_back(w0);

    i = j;
  }

  if(b)
    ans.push_back(0);
  sort(all(ans));

  if(ans.empty()){
    cout << "IMPOSSIBLE" << endl;
  }else{
    for(int x: ans)
      cout << x << endl;
  }
  return 0;
}
