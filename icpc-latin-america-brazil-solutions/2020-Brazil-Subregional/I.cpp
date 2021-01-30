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
inline int modSum(int a, int b, int mod = MOD){
  int ans = a+b;
  if(ans > mod) ans -= mod;
  return ans;
}
inline int modSub(int a, int b, int mod = MOD){
  int ans = a-b;
  if(ans < 0) ans += mod;
  return ans;
}
inline int modMul(int a, int b, int mod = MOD){
  return (a*1LL*b)%mod;
}
ll extGcd(ll a, ll b, ll &x, ll &y){
  if (b == 0){
    x = 1, y = 0;
    return a;
  }else{
    ll g = extGcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
  }
}
int inv(int a, int mod=MOD){
  ll inv_x, y;
  extGcd(a, mod, inv_x, y);
  return (inv_x%mod + mod)%mod;   
}
int modDiv(int a, int b, int mod = MOD){
  return modMul(a, inv(b, mod));
}
const int MAXN = 100010;
vector<int> adj[MAXN];
int dp[MAXN][2];
int solve(int u, bool b){
  if(dp[u][b] != -1)
    return dp[u][b];
  if(adj[u].size() == 0)
    return 1;
  int m = adj[u].size();
  vector<int> s(m+2), p(m+2);

  p[0] = 1;
  for(int i=1; i<=m; i++)
    p[i] = modMul(p[i-1], solve(adj[u][i-1], 0));
  s[m+1] = 1;
  for(int i=m; i>=1; i--)
    s[i] = modMul(s[i+1], solve(adj[u][i-1], 0));
  if(b){
    int ans = 0;
    for(int i=1; i<=m; i++)
      ans = modSum(ans, modMul(p[i-1], modMul(solve(adj[u][i-1], 1), s[i+1])));
    return dp[u][b] = ans;
  }else{
    int ans = 0;
    for(int i=1; i<=m; i++)
      ans = modSum(ans, modMul(p[i-1], modMul(solve(adj[u][i-1], 1), s[i+1])));
    return dp[u][b] = modSum(s[1], ans);
  }
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(dp, -1, sizeof(dp));
  int n;
  cin >> n;
  vector<int> v(n);
  for(int i=2; i<=n; i++){
    int x;
    cin >> x;
    adj[x].push_back(i);
  }
  cout << solve(1, 0) << endl;
  return 0;
}
