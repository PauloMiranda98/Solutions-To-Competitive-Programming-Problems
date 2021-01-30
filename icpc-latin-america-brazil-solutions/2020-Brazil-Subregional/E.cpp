#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define endl '\n'

using namespace std;

using ll = long long;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};

const int MAXN = 100010;
vector<int> queries[MAXN];
vector<int> adj[MAXN];
int level[MAXN];
int P[MAXN][22];
int n, mxLogN=20;
void build(int root = 1){
  P[root][0] = root;
  for (int j = 1; j <= mxLogN; j++)
    for (int i = 1; i <= n; i++){
      P[i][j] = P[P[i][j - 1]][j - 1];
    }
}
class Bit{
private:
  typedef long long t_bit;
  int nBit;
  int nLog;
  vector<t_bit> bit;
public:
  Bit(int m){
    nBit = m;
    nLog = 20;
    bit.resize(nBit + 1, 0);
  }
  //1-indexed
  t_bit get(int i){
    t_bit s = 0;
    for (; i > 0; i -= (i & -i))
      s += bit[i];
    return s;
  }
  //1-indexed [l, r]
  t_bit get(int l, int r){
    return get(r) - get(l - 1);
  }
  //1-indexed
  void add(int i, t_bit value){
    assert(i > 0);
    for (; i <= nBit; i += (i & -i))
      bit[i] += value;
  }
  t_bit lower_bound(t_bit value){
    t_bit sum = 0;
    int pos = 0;
    for (int i = nLog; i >= 0; i--){
      if ((pos + (1 << i) <= nBit) and (sum + bit[pos + (1 << i)] < value)){
        sum += bit[pos + (1 << i)];
        pos += (1 << i);
      }
    }
    return pos + 1;
  }
};

int v[MAXN];
int ans[MAXN];
Bit bit(MAXN);
void solve(int u){
  for(int l: queries[u])
    bit.add(l, +1);
  ans[u] = bit.get(v[u]);
  for(int to: adj[u])
    solve(to);
  for(int l: queries[u])
    bit.add(l, -1);
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int m;
  cin >> n >> m;
  int u = 0;
  for(int i=1; i<=n; i++){
    cin >> v[i];
    cin >> P[i][0];
    if(i != P[i][0])
      adj[P[i][0]].push_back(i);
    else
      u = i;
  }
  build(u);
  for(int i=0; i<m; i++){
    int x, l, r;
    cin >> x >> l >> r;
    for(int j=20; j>=0; j--){
      int p = P[x][j];
      if(v[p] <= r)
        x = p;
    }
    queries[x].push_back(l);
  }
  solve(u);
  for(int i=1; i<=n; i++)
    cout << ans[i] << " ";
  cout << endl;
  
  return 0;
}
