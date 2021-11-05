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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int b, l;
  cin >> b >> l;

  vector<ll> d(l+1);
  for(int i=1; i<=l; i++){
    cin >> d[i];
  }
  int mod = b+1;

  vector<ll> pb(l+1);
  pb[0] = 1;
  for(int i=1; i<=l; i++){
    pb[i] = (pb[i-1]*b)%mod;
  }
  ll sum = 0;
  for(int i=1; i<=l; i++){
    sum = ((sum*b)%mod + d[i])%mod;
  }

  for(int i=1; i<=l; i++){
    ll x = (sum - (d[i]*pb[l-i])%mod + mod)%mod;

    ll p = inv(pb[l-i], mod);
    int j = ((mod-x)*p)%mod;
    if(j < d[i]){
      x = (x + (pb[l-i]*j)%mod)%mod;
      if(x == 0){
        cout << i << " " << j << endl;
        return 0;
      }
    }
  }
  if(sum == 0)
    cout << 0 << " " << 0 << endl;
  else
    cout << -1 << " " << -1 << endl;
  return 0;
}
