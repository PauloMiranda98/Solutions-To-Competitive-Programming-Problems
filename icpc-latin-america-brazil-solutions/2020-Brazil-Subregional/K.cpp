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
const int MAXB = 102;
struct GaussXOR {
  __int128_t table[MAXB];
  GaussXOR() {
    for(int i = 0; i < MAXB; i++) {
      table[i] = 0;
    }
  }
  int size() {
    int ans = 0;
    for(int i = 0; i < MAXB; i++) {
      if(table[i]) ans++;
    }
    return ans;
  }
  bool isComb(__int128_t x) {
    for(int i = MAXB-1; i >= 0; i--) {
      x = std::min(x, x ^ table[i]);
    }
    return x == 0;
  }
  void add(__int128_t x) {
    for(int i = MAXB-1; i >= 0; i--) {
      if( (table[i] == 0) and ((x>>i) & 1)){
        table[i] = x;
        x = 0;
      } else {
        x = std::min(x, x ^ table[i]);
      }
    }
  }
};

const int MAXN = 110;
int g[MAXN];
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int n, m;
  cin >> n >> m;
  vector<vector<int>> mat(n, vector<int>(n+1, 0));
  
  for(int i=0; i<m; i++){
    int a, b;
    cin >> a >> b;
    a--; b--;
    mat[a][b] = 1;
    mat[b][a] = 1;
    g[a]++;
    g[b]++;
  }
  GaussXOR gauss;
  for(int i=0; i<n; i++){
    if(g[i]%2 == 0)
      mat[i][n] = 1;
    else
      mat[i][i] = 1;
    __int128_t x = 0, one = 1;
    for(int j=0; j<=n; j++){
      if(mat[i][j])
        x |= (one<<j);
    }
    gauss.add(x);
  }
  __int128_t one = 1;
  if(!gauss.isComb(one<<n))
    cout << 'Y' << endl;
  else
    cout << 'N' << endl;
  return 0;
}
