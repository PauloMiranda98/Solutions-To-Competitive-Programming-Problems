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
  const uint64_t MOD = (1ll<<61) - 1;
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
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, m;
  cin >> n >> m;
  
  unordered_set<ll> sta, stb;
  vector<StringHashing> v1, v2;
  for(int i=0; i<n; i++){
    string s;
    cin >> s;
    int k = s.size();
    StringHashing sh(s);
    v1.push_back(sh);
    sta.insert(sh.getValue(0, k-1));
  }
  for(int i=0; i<m; i++){
    string s;
    cin >> s;
    int k = s.size();
    StringHashing sh(s);
    v2.push_back(sh);
    stb.insert(sh.getValue(0, k-1));
  }
  unordered_set<ll> st1, st2;
  for(auto &sh: v1){
    int k = sh.p.size();
    for(int i=0; i<k-1; i++)
      if(sta.count(sh.getValue(0, i)))
        st1.insert(sh.getValue(i+1, k-1));
  }
  for(auto &sh: v2){
    int k = sh.p.size();
    for(int i=1; i<k; i++)
      if(stb.count(sh.getValue(i, k-1)))
        st2.insert(sh.getValue(0, i-1));
  }
  unordered_set<ll> ans1, ans2;
  for(auto &sh: v1){
    int k = sh.p.size();
    for(int i=0; i<k-1; i++){
      if(sta.count(sh.getValue(0, i)) and st2.count(sh.getValue(i+1, k-1))){
        ans1.insert(sh.getValue(0, k-1));
        ans1.insert(sh.getValue(0, i));
      }
    }
  }
  for(auto &sh: v2){
    int k = sh.p.size();
    for(int i=1; i<k; i++){
      if(stb.count(sh.getValue(i, k-1)) and st1.count(sh.getValue(0, i-1))){
        ans2.insert(sh.getValue(i, k-1));
        ans2.insert(sh.getValue(0, k-1));
      }
    }
  }
  
  cout << n - ans1.size() << " " << m - ans2.size() << endl;
  return 0;
}
