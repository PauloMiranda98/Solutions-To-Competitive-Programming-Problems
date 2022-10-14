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

int x1, x2, x3;
int dp[33][2][2][2];

int solve(int i, int f1, int f2, int f3){
  if(i == -1)
    return 1;
  
  if(dp[i][f1][f2][f3] != -1)
    return dp[i][f1][f2][f3];
  
  int b1 = ((x1>>i)&1) or f1;
  int b2 = ((x2>>i)&1) or f2;
  int b3 = ((x3>>i)&1) or f3;
  
  int ans = 0;
  
  for(int c1=0; c1 <= b1; c1++){
    for(int c2=0; c2 <= b2; c2++){
      for(int c3=0; c3 <= b3; c3++){
        if((c1 ^ c2 ^ c3) == 0){
          ans = ans + solve(i-1, f1 or (c1 < b1), f2 or (c2 < b2), f3 or (c3 < b3));
          ans %= MOD;
        }
      }
    }
  }

  return dp[i][f1][f2][f3] = ans;
}

int calcDp(int a, int b, int c){
  memset(dp, -1, sizeof(dp));
  
  x1 = a;
  x2 = b;
  x3 = c;
  
  return solve(30, false, false, false);
}

typedef long long ll;
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

inline int modMul(int a, int b, int mod = MOD){
  return (a*1LL*b)%mod;
}

int inv(int a, int mod=MOD){
  assert(a > 0);
  ll inv_x, y;
  extGcd(a, mod, inv_x, y);
  return (inv_x%mod + mod)%mod;
}

int modDiv(int a, int b, int mod = MOD){
  return modMul(a, inv(b, mod));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int l1, r1, l2, r2, l3, r3;
  
  cin >> l1 >> r1;
  cin >> l2 >> r2;
  cin >> l3 >> r3;
  
  ll ans = modMul(modMul(r1-l1+1, r2-l2+1), r3-l3+1);
  ans -= calcDp(r1, r2, r3);

  ans += calcDp(l1-1, r2, r3);
  ans += calcDp(r1, l2-1, r3);
  ans += calcDp(r1, r2, l3-1);

  ans -= calcDp(l1-1, l2-1, r3);
  ans -= calcDp(l1-1, r2, l3-1);
  ans -= calcDp(r1, l2-1, l3-1);

  ans += calcDp(l1-1, l2-1, l3-1);

  ans %= MOD;
  ans = (ans + MOD)%MOD;
  
  ans = modDiv(ans, r1-l1+1);
  ans = modDiv(ans, r2-l2+1);
  ans = modDiv(ans, r3-l3+1);
  
  cout << ans << endl;
  
  return 0;
}
