#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define endl '\n'

using namespace std;
const int MOD = 1000000007;
typedef pair<int, int> pii;
class MergeSortTree{
private:
  typedef vector<pii> Node;
  Node neutral;
  vector<Node> st;
  int n;
  inline void join(Node &a, Node &b, Node &ans){
    ans.resize(a.size() + b.size());
    merge(all(a), all(b), ans.begin());
  }
public:
  template <class MyIterator>
  MergeSortTree(MyIterator begin, MyIterator end){
    int sz = end - begin;
    for (n = 1; n < sz; n <<= 1);
    st.assign(n << 1, neutral);
    for (int i = 0; i < sz; i++, begin++)
      st[i + n] = *begin;
    for (int i = n - 1; i; i--){
      int l = (i << 1); 
      join(st[l], st[l+1], st[i]);
    }
  }
  void push(vector<int> &ans, int node, int k){
    for(auto p: st[node]){
      if(p.first < k)
        ans.push_back(p.second);
      else
        break;
    }
  }
  vector<int> query(int l, int r, int k){
    vector<int> ans;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1){
      if (l & 1)
        push(ans, l++, k);
      if (r & 1)
        push(ans, --r, k);
    }
    return ans;
  }
};
typedef long long ll;
vector<ll> cc;
int getV(ll x){
  return lower_bound(all(cc), x) - cc.begin();
}
typedef tuple<ll, ll, int> tp;
void transform(ll &x, ll &y){
  ll a = x - 2*y;
  ll b = x + 2*y;
  x = a; y = -b;
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, q;
  cin >> n >> q;
  vector<tp> v(n);
  
  for(int i=0; i<n; i++){
    auto &[x, y, id] = v[i];
    cin >> x >> y;
    transform(x, y);
    id = i+1;
    cc.push_back(x);
    cc.push_back(y);
  }
  sort(all(cc));
  cc.erase(unique(all(cc)), cc.end());
  vector<vector<pii>> vv(cc.size());
  for(int i=0; i<n; i++){
    auto &[a, b, id] = v[i];
    int x = getV(a);
    int y = getV(b);
    vv[x].push_back(pii(y, id));
  }
  int m = cc.size();
  for(int i=0; i<m; i++){
    sort(all(vv[i]));
  }
  MergeSortTree mst(vv.begin(), vv.end());
  int p = 0;
  cc.push_back(0x3f3f3f3f);
  for(int i=0; i<q; i++){
    int a, b;
    cin >> a >> b;
    ll x = -1 - ((p + a)%MOD);
    ll y = (p + b)%MOD;
    transform(x, y);
    x = getV(x);
    y = upper_bound(all(cc), y) - cc.begin();
    auto vAns = mst.query(x, m-1, y);
    sort(all(vAns));
    p = 0;
    ll base = 5782344;
    ll pw = 1;
    for(int value: vAns){
      p = (p + (value*pw)%MOD)%MOD;
      pw = (pw*base)%MOD;
    }
    cout << p << endl;
  }
  return 0;
}
