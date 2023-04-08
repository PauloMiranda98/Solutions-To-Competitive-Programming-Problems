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

struct StringHashing{
  const uint64_t MOD = (1LL<<61) - 1;
  const int base = 31;
  uint64_t modMul(uint64_t a, uint64_t b){
    uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
    uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    uint64_t ret = (l&MOD) + (l>>61) + (h << 3) + (m >> 29) + ((m << 35) >> 3) + 1;
    ret = (ret & MOD) + (ret>>61);
    ret = (ret & MOD) + (ret>>61);
    return ret-1;
  }
  int getInt(char c){
    return c-'a'+1;
  }
  vector<uint64_t> hs, p;
//Public:
  StringHashing(string s){
    int n = s.size();
    hs.resize(n); p.resize(n);
    p[0] = 1;
    hs[0] = getInt(s[0]);
    for(int i=1; i<n; i++){
      p[i] = modMul(p[i-1], base);
      hs[i] = (modMul(hs[i-1], base) + getInt(s[i]))%MOD;
    }
  }
  uint64_t getValue(int l, int r){
    if(l > r) return -1;
    uint64_t res = hs[r];
    if(l > 0) res = (res + MOD - modMul(p[r-l+1], hs[l-1]))%MOD;
    return res;
  }
};

string s;
StringHashing *sh;
int n, d;

int solve(int i){
  if(i == n)
    return 0;
  
  int mx = i+1;

  for(int k=1; k<=d; k++){
    int j= i + k;
    for(; j<=n; j+=k){
      if(sh->getValue(i, i+k-1) == sh->getValue(j-k, j-1)){
        mx = max(mx, j);
      }else{
        break;
      }      
    }

    j = j - k;

    int eq = 0;
    while(j + eq < n and s[i + eq] == s[j + eq]){
      eq++;
    }
    
    mx = max(mx, j + eq);
  }
  
  return solve(mx) + 1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  cin >> s;
  cin >> d;
  
  n = s.size();
  sh = new StringHashing(s);
  cout << solve(0) << endl;
  
  delete sh;  
  return 0;
}
