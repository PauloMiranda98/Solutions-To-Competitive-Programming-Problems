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

typedef unsigned long long ull;

ull fastPow(ull base, ull exp, ull mod){
  base %= mod;
  //exp %= phi(mod) if base and mod are relatively prime
  ull ans = 1LL;
  while (exp > 0){
    if (exp & 1LL)
      ans = (ans * (__int128_t)base) % mod;
    base = (base * (__int128_t)base) % mod;
    exp >>= 1;
  }
  return ans;
}
ull modMul(ull a, ull b, ull mod){
  return (a * (__uint128_t)b) % mod;
}
bool checkComposite(ull n, ull a, ull d, int s){
  ull x = fastPow(a, d, n);
  if (x == 1 or x == n - 1)
    return false;
  for (int r = 1; r < s; r++){
    x = modMul(x, x, n);
    if (x == n - 1LL)
      return false;
  }
  return true;
};
bool millerRabin(ull n){
  if (n < 2)
    return false;
  int r = 0;
  ull d = n - 1LL;
  while ((d & 1LL) == 0){
    d >>= 1;
    r++;
  }
  for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
    if (n == a)
      return true;
    if (checkComposite(n, a, d, r))
      return false;
  }
  return true;
}
ull pollard(ull n){
  auto f = [n](ull x) { return modMul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1){
    if (x == y)
      x = ++i, y = f(x);
    if ((q = modMul(prd, max(x, y) - min(x, y), n)))
      prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}
vector<ull> factor(ull n){
  if (n == 1)
    return {};
  if (millerRabin(n))
    return {n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int m, n, k;
  cin >> m >> n >> k;
  set<ull> st;
  for(int i=0; i<n; i++){
    ull x;
    cin >> x;
    for(auto p: factor(x))
      st.insert(p);
  }
  for(int i=0; i<k; i++){
    int a, b, c;
    cin >> a >> b >> c;
  }
  for(auto x: st)
    cout << x << " ";
  cout << endl;
  return 0;
}
