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

struct Line{
  int k, b;
  Line(int k, int b): k(k), b(b) {}
  ll eval(int x) {
    return k *(ll) x + b;
  }
};
struct PersistentLiChaoTree {
private:
  struct LiChaoNode {
    Line line;
    int l, r;
    LiChaoNode(Line line) : line(line), l(0), r(0) {}
  };
  vector<LiChaoNode> t;
  int T;
  int clone(LiChaoNode r){
    t.emplace_back(r);
    return ++T;
  }
  int update(int id, Line nw, int l, int r) {
    int m = (l + r - 1) / 2;
    bool lef = nw.eval(l) < t[id].line.eval(l);
    bool mid = nw.eval(m) < t[id].line.eval(m);
    if(mid) swap(t[id].line, nw);
    if(l == r) return id;
    if(lef != mid) {
      t[id].l = clone(t[t[id].l]);
      update(t[id].l, nw, l, m);
    } else {
      t[id].r = clone(t[t[id].r]);
      update(t[id].r, nw, m + 1, r);
    }
    return id;
  }
  ll queryMin(int cur, int x, int l, int r) {
    ll val = t[cur].line.eval(x);
    int m = (l + r - 1) / 2;
    if(l < r) {
      if(x <= m && t[cur].l) val = min(val, queryMin(t[cur].l, x, l, m));
      if(x > m && t[cur].r) val = min(val, queryMin(t[cur].r, x, m + 1, r));
    }
    return val;
  }
  int L, R;
  vector<int> roots;
public:
  PersistentLiChaoTree(int L=-INF, int R=INF) : L(L), R(R) {
    t.emplace_back(Line(0LL, INF));
    T = 0;
    
    roots.push_back(clone(t.front()));
  }
  int lastVersion(){
    return (int)roots.size() - 1;
  }
  int addLine(Line line, int version) {
    auto root = t[roots[version]];
    int newRootId = clone(root);
    update(newRootId, line, L, R);
    roots.push_back(newRootId);
    return lastVersion();
  }
  int addLine(Line line){
    return addLine(line, lastVersion());
  }
  ll queryMin(int version, int x) {
    return queryMin(roots[version], x, L, R);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;

  vector<pii> vp(n);
  for(int i=0; i<n; i++)
    cin >> vp[i].F >> vp[i].S;
  
  int p;
  cin >> p; 

  PersistentLiChaoTree plct;

  for(int i=0; i<p; i++){
    int k, b;
    cin >> k >> b;
    Line l(-k, -b);
    plct.addLine(l);
  }
  
  vector<vector<int>> res(p);
  
  for(int i=0; i<n; i++){
    auto [x, y] = vp[i];
    
    int lo=0, hi=p-1, ans = -1;
    while(lo <= hi){
      int mid = (lo + hi)/2;
      
      auto ymid = -plct.queryMin(mid + 1, x);
      
      if(ymid > y){
        ans = mid;
        hi = mid - 1;
      }else{
        lo = mid + 1;
      }
    }
    
    if(ans != -1)
      res[ans].push_back(i+1);
  }
  
  for(auto v: res){
    cout << v.size();
    for(int x: v)
      cout << " " << x;
    cout << endl;
  }
  
  return 0;
}
