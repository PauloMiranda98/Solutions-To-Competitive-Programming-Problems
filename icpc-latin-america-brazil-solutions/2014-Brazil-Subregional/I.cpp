#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int fastPow(int base, int exp, int mod){
  int ans = 1;
  while (exp > 0){
    if (exp & 1)
      ans = (ans*1LL*base) % mod;
    base = (base*1LL*base) % mod;
    exp >>= 1;
  }
  return ans;
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

int inv(int a, int mod){
  ll inv_x, y;
  extGcd(a, mod, inv_x, y);
  return (inv_x%mod + mod)%mod;   
}

int nthPhi(int n){
  int result = n;
  for (int i = 2; i <= n / i; i++){
    if (n % i == 0){
      while (n % i == 0)
        n /= i;
      result -= result / i;
    }
  }
  if (n > 1)
    result -= result / n;
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, e, c;
  cin >> n >> e >> c;
  int phiN = nthPhi(n);
  int d = inv(e, phiN);
  cout << fastPow(c, d, n) << endl;
  return 0;
}
