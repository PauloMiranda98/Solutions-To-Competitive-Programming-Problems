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
const int MOD = 998244353;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};

struct RollbackUF {
  vector<int> e; 
  vector<tuple<int, int, int, int>> st;
  RollbackUF(int n) : e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return st.size(); }
  void rollback(int t) {
    while (st.size() > t){
      auto [a1, v1, a2, v2] = st.back();
      e[a1] = v1; e[a2] = v2;
      st.pop_back();
    }
  }
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, e[a], b, e[b]});
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

const int MAXN = 110;

bool mat[MAXN][MAXN];

int n;

inline void apply(int i){
  for(int j=1; j<=n; j++)
    mat[i][j] ^= 1;
  for(int j=1; j<=n; j++)
    mat[j][i] ^= 1;
}

RollbackUF uf(MAXN);
int solve(int i, int qtd){
  if(i > n)
    return qtd == n-1;
  int ans = 0;
  {
    bool ok = true;
    int v = uf.time();
    int newQtd = qtd;
    for(int j=1; j<i; j++){
      if(mat[i][j]){
        if(uf.find(i) != uf.find(j)){
          uf.unite(i, j);
          newQtd++;
        }else{
          ok = false;
        }
      }
    }
    if(ok)
      ans += solve(i+1, newQtd);
    uf.rollback(v);
  }

  {
    apply(i);
    bool ok = true;
    int v = uf.time();
    int newQtd = qtd;
    for(int j=1; j<i; j++){
      if(mat[i][j]){
        if(uf.find(i) != uf.find(j)){
          uf.unite(i, j);
          newQtd++;
        }else{
          ok = false;
        }
      }
    }
    if(ok)
      ans += solve(i+1, newQtd);
    apply(i);
    uf.rollback(v);
  }
  
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int m;
  cin >> n >> m;
  for(int i=0; i<m; i++){
    int a, b;
    cin >> a >> b;
    mat[a][b] = true;
    mat[b][a] = true;
  }
  cout << solve(1, 0) << endl;
  return 0;
}
