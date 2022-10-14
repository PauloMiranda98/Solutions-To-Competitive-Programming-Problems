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

const int MAXN = 100010;

bitset<MAXN> bs;
vector<int> primes;

void sieve(int l) {
  int ns = l+1;
  bs.set();
  primes.clear();
  bs[0] = bs[1] = 0;
  for (ll i = 2; i < ns; i++) if (bs[i]) {
    for(ll j = i*i; j < ns; j += i) 
      bs[j] = 0;
    primes.push_back(i);
  }
}

int mobius[MAXN];
void sieveMobius(ll l) {
  sieve(l);
  mobius[1] = 1;
  for(int i=2; i<=l; i++)
    mobius[i] = 0;
  for(ll p: primes){
    if(p > l) break;
    for(ll j = p; j <= l; j += p){
      if(mobius[j] != -1){
        mobius[j]++;
        if(j%(p*p) == 0)
          mobius[j] = -1;
      }
    }
  }
  for(int i=2; i<=l; i++){
    if(mobius[i] == -1)
      mobius[i] = 0;
    else if(mobius[i]%2 == 0)
      mobius[i] = 1;
    else
      mobius[i] = -1;
  }
}

vector<int> mobiusDiv[MAXN];

void build(int n){
  sieveMobius(n);
  
  for(int i=2; i<=n; i++) if(mobius[i] != 0){
    for(int j=i; j<=n; j+=i){
      mobiusDiv[j].push_back(i);
    }
  }
  
  int mx = 0;
  for(int i=1; i<=n; i++)
    mx = max(mx, (int)mobiusDiv[i].size());
  
  // 30030 = 2*3*5*7*11*13
  assert(mx <= 64);
}

int n;
int ans[MAXN];
int A[MAXN];
pii op[MAXN];

ll total[MAXN];

bool test(int c){
  
  ll sum = 0;
  for(int x: mobiusDiv[c]){
    sum += mobius[x] * total[x];
  }
  sum = abs(sum);
  
  return sum >= A[c];
}

void add(int k){
  auto[c, d] = op[k];
  
  for(int x: mobiusDiv[c]){
    total[x] += d;
  }
}

void remove(int k){
  auto[c, d] = op[k];
  
  for(int x: mobiusDiv[c]){
    total[x] -= d;
  }
}

void solve(int i, int j, vector<int> &v){
  if(v.empty())
    return;
  if(i == j){
    for(int x: v)
      ans[x] = i;
    return;
  }
  int mid = (i+j)/2;
  for(int k=i; k<=mid; k++) 
    add(k);
  vector<int> left, right;
  for(int x: v){
    if(test(x))
      left.push_back(x);
    else
      right.push_back(x);
  }
  solve(mid+1, j, right);
  for(int k=mid; k>=i; k--)
    remove(k);
  solve(i, mid, left);
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  build(100000);

  int q;
  cin >> n >> q;

  for(int i=1; i<=n; i++){
    cin >> A[i];
    ans[i] = -1;
  }
  
  for(int i=0; i<q; i++){
    cin >> op[i].F >> op[i].S;
  }
  
  vector<int> v(n, 1);
  iota(v.begin(), v.end(), 1);
  
  solve(0, q, v);
  
  for(int i=1; i<=n; i++){
    if(ans[i] == q)
      cout << -1 << endl;
    else
      cout << ans[i] + 1 << endl;
  }
  
  return 0;
}
