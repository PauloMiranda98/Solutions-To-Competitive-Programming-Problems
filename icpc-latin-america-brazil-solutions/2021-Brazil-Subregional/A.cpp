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
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};

typedef long long ll;
const int MOD = 1e9 + 7;
struct modInt{
  int val;
  modInt(ll v = 0) {
    if (v < 0)
      v = (v % MOD) + MOD;
    if (v >= MOD)
      v %= MOD;
    val = v;
  }
  explicit operator int() const {
    return val;
  }
  modInt operator+(const modInt &oth) {
    int ans = val + oth.val;
    if (ans >= MOD) 
      ans -= MOD;
    return modInt(ans);
  }
  modInt operator-(const modInt &oth) {
    int ans = val - oth.val;
    if (ans < 0) ans += MOD;
    return ans;
  }
  modInt operator*(const modInt &oth) {
    return ((uint64_t) val * oth.val) % MOD;
  }
  modInt operator-() const {
    return (val == 0) ? 0 : MOD - val;
  }
  bool operator==(const modInt &oth) const {
    return val == oth.val;
  }
  bool operator!=(const modInt &oth) const {
    return val != oth.val;
  }
  static int modInv(int a, int m = MOD) {
    int g = m, r = a, x = 0, y = 1;
    while (r != 0) {
      int q = g / r;
      g %= r; swap(g, r);
      x -= q * y; swap(x, y);
    }
    return x < 0 ? x + m : x;
  }
  modInt inv() const {
    return modInv(val);
  }
  modInt operator/(const modInt &oth) {
    return (*this) * oth.inv();
  }
  modInt pow(long long p) const {
    assert(p >= 0);
    modInt a = *this, result = 1;
    while (p > 0) {
      if (p & 1)
        result = result * a;
      a = a * a;
      p >>= 1;
    }
    return result;
  }
};

namespace LagrangePoly {
  const int MAXN = 100010;
  modInt den[MAXN], fat[MAXN], ifat[MAXN], l[MAXN], r[MAXN];

  void build(int n){
    fat[0] = 1;
    for(int i=1; i<=n; i++)
      fat[i] = fat[i-1] * i;
    ifat[n] = fat[n].inv();
    for(int i=n-1; i>=0; i--)
      ifat[i] = ifat[i+1] * (i+1);
  }
  // f(i) = y[i]
  //return f(x0)
  modInt getVal(vector<modInt> y, ll x0) {
    int n = y.size();
    assert(fat[n-1] != 0);
    
    modInt x = x0;
    for(int i = 0; i < n; i++) {
      den[i] = ifat[n - i - 1] * ifat[i];
      if((n - i - 1) % 2 == 1) {
        den[i] = -den[i];
      }
    }
    
    l[0] = 1;
    for(int i = 1; i < n; i++) {
      l[i] = l[i - 1] * (x - (i - 1));
    }
    r[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--) {
      r[i] = r[i + 1] * (x - (i + 1));
    }
    modInt ans = 0;
    for(int i = 0; i < n; i++) {
      modInt li = l[i] * r[i] * den[i];
      ans = (ans + (y[i] * li));
    }
    return ans;
  }
};


const int MAXN = 5010;
vector<modInt> dp[MAXN];
// dp[i][x] = sum_v[i]<=j<=x dp[i+1][j]
// dp[i][x] = (sum_0<=j<=x dp[i+1][j]) - (sum_0<=j<v[i] dp[i+1][j])
// solve = dp[0][r]
int v[MAXN];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, r;
  cin >> n >> r;
  LagrangePoly::build(n+1);
  
  for(int i=0; i<n; i++){
    cin >> v[i];
  }
  int mx = 0;
  for(int i=n-1; i>=0; i--){
    mx = max(mx, v[i]);
    v[i] = mx;
  }
  if(mx > r){
    cout << 0 << endl;
    return 0;
  }
  dp[n].resize(n+1, 1);
  
  for(int i=n-1; i>=0; i--){
    vector<modInt> q(n+1, 0);
    modInt sum = 0;
    for(int j=0; j<=n; j++){
      sum = sum + dp[i+1][j];
      q[j] = sum;
    }
    modInt c = LagrangePoly::getVal(q, v[i] - 1);
    dp[i].resize(n+1, 0);
    for(int j=0; j<=n; j++){
      dp[i][j] = q[j] - c;
    }
  }
  cout << (int)LagrangePoly::getVal(dp[0], r) << endl;
  
  return 0;
}
