#include <bits/stdc++.h>
#define T first
#define S second
#define all(x) x.begin(),x.end()
#define endl '\n'
 
using namespace std;
 
using ll = long long;
using pii = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};

ll currT1;
ll currT2;

struct Node{
  ll t0, s;
  int version, id;
  
  Node(ll _t0, ll _s, int _version, int _id): t0(_t0), s(_s), version(_version), id(_id) {}
  
  ll T(){
    if(version == 1)
      return currT1;
    else if(version == 2)
      return currT2;
    else
      assert(false);
  }
  
  ll value(){
    return (T() - t0) * s;
  }
  
  pii cmpValue(){
    return pii(value(), s);
  }
  
  bool isLt(Node &oth){
    return cmpValue() < oth.cmpValue();
  }
  
  bool isLe(Node &oth){
    return cmpValue() <= oth.cmpValue();
  }
};

struct Bit{
  vector<ll> bit;
  
  void build(int n){
    bit.assign(n + 1, 0);
  }
  void _add(int i, ll x){
    i++;
    for(; i < (int)bit.size(); i += i&-i)
      bit[i] += x;
  }
  ll query(int i){
    i++;
    ll sum = 0;
    for(; i > 0; i -= i&-i)
      sum += bit[i];
    return sum;
  }
  void addRange(int a, int b, ll x){
    _add(a, x);
    _add(b+1, -x);
  }
  void swap(int i, int j){
    ll a = query(i);
    ll b = query(j);
    addRange(i, i, - a + b);
    addRange(j, j, - b + a);
  }
};

struct Set{
  vector<Node> v;
  vector<int> pos;
  Bit bit;
  int ver;
  
  Set(int version){
    ver = version;
  }
  
  void build(vector<pii> vp){
    pos.resize(vp.size());
    bit.build((int)vp.size());
    
    int id = 0;
    for(auto p: vp)
      v.emplace_back(p.T, p.S, ver, id++);
    
    sort(all(v), [&](Node &a, Node &b){
      return a.isLt(b);
    });
    
    for(int i=0; i<(int)v.size(); i++){
      pos[v[i].id] = i;
    }
  }
  
  int id(int i){
    return v[i].id;
  }

  ll value(int i){
    return bit.query(i);
  }
    
  void fixUp(int id){
    while(pos[id] + 1 < (int)v.size()){
      int p = pos[id];
      
      if(v[p].isLe(v[p+1]))
        break;
      
      int nxt = v[p+1].id;
      
      swap(v[p], v[p+1]);
      swap(pos[id], pos[nxt]);

      bit.swap(p, p+1);
    }
  }

  void fix(vector<int> ids){
    sort(all(ids), [&](int &a, int &b){
      return pos[a] > pos[b];
    });
    
    for(int id: ids)
      fixUp(id);
  }

  void addRange(ll a, ll b, ll x){
    int l = lower_bound(a);
    int r = upper_bound(b);
    if(l == r)
      return;

    bit.addRange(l, r-1, x);
  }
  
  int count(ll a, ll b){
    return upper_bound(b) - lower_bound(a);
  }

  int lower_bound(ll x){
    int lo=0, hi=(int)v.size()-1, ans=(int)v.size();
    while(lo <= hi){
      int mid = (lo+hi)/2;
      
      if(v[mid].value() >= x){
        ans = mid;
        hi = mid - 1;
      }else{
        lo = mid + 1;
      }
    }
    return ans;
  }

  int upper_bound(ll x){
    int lo=0, hi=(int)v.size()-1, ans=(int)v.size();
    while(lo <= hi){
      int mid = (lo+hi)/2;
      
      if(v[mid].value() > x){
        ans = mid;
        hi = mid - 1;
      }else{
        lo = mid + 1;
      }
    }
    return ans;
  }

};

// (t - a.T)*a.S = (t - b.T)*b.S

// t*a.S - a.T*a.S = t*b.S - b.T*b.S

bool fistTimeAfterIntersect(pii a, pii b, ll &nt){
  if(a.S == b.S)
    return false;

  ll n = a.T*a.S - b.T*b.S;
  ll d = a.S - b.S;

  if(d < 0){
    n = -n;
    d = -d;
  }
  
  nt = (n + d-1)/d;
  return true;
}

Set st1(1), st2(2);

void updateTimeSet1(ll t){
  currT1 = t;
}

void updateTimeSet2(ll t){
  currT2 = t;
}

void buildSet1(vector<pii> v){
  updateTimeSet1(0);  
  st1.build(v);
}

void buildSet2(vector<pii> v){
  updateTimeSet2(0);
  st2.build(v);
}

void fixSet1(vector<int> ids){
  st1.fix(ids);
}

void fixSet2(vector<int> ids){
  st2.fix(ids);
}

bool hasSet1(ll a, ll b){
  return st1.count(a, b) > 0;
}

void addRangeSet2(ll a, ll b){
  st2.addRange(a, b, +1);
}

vector<int> buildAnswerSet2(int n){
  vector<int> ans(n, 0);
  for(int i=0; i<n; i++){
    int id = st2.id(i);
    int v = (int)st2.value(i);

    ans[id] = v;
  }
  return ans;
}

const int FIX1 = 0;
const int FIX2 = 1;
const int QUERY = 2;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int r;  
  cin >> r;
  
  vector<pii> runners(r);
  for(int i=0; i<r; i++)
    cin >> runners[i].T >> runners[i].S;
  
  int p;
  cin >> p;
  vector<tuple<int, int, int>> photos;
  
  for(int i=0; i<p; i++){
    int t, a, b;
    cin >> t >> a >> b;
    photos.emplace_back(t, a, b); 
  }
  
  int q;
  cin >> q;
  
  vector<pii> v(q);
  for(int i=0; i<q; i++)
    cin >> v[i].T >> v[i].S;
  
  // Build sets
  buildSet1(runners);
  buildSet2(v);
  
  // time, type, a, b, ids
  vector<tuple<int, int, int, int, vector<int>>> events;
  
  // Add events of queries
  for(auto [t, a, b]: photos)
    events.emplace_back(t, QUERY, a, b, vector<int>());
  
  // Add events of fixes 1
  unordered_map<int, vector<int>> mp1;
  for(int i=0; i<r; i++){
    for(int j=i+1; j<r; j++){
      ll nt;
      if(fistTimeAfterIntersect(runners[i], runners[j], nt)){
        if(nt > 0 && nt < INF){
          mp1[(int)nt].push_back(i);
          mp1[(int)nt].push_back(j);
        }
      }
    }
  }
  for(auto &[t, ids]: mp1)
    events.emplace_back(t, FIX1, 0, 0, ids);
    
  // Add events of fixes 2
  unordered_map<int, vector<int>> mp2;
  for(int i=0; i<q; i++){
    for(int j=i+1; j<q; j++){
      ll nt;
      if(fistTimeAfterIntersect(v[i], v[j], nt)){
        if(nt > 0 && nt < INF){
          mp2[(int)nt].push_back(i);
          mp2[(int)nt].push_back(j);
        }
      }
    }
  }
  for(auto &[t, ids]: mp2)
    events.emplace_back(t, FIX2, 0, 0, ids);
  
  sort(events.begin(), events.end());
  
  for(auto [t, tp, a, b, ids]: events){
    updateTimeSet1(t);
    updateTimeSet2(t);
    
    if(tp == FIX1){
      fixSet1(ids);
    }else if(tp == FIX2){
      fixSet2(ids);
    }else if(tp == QUERY){
      if(hasSet1(a, b)){
        addRangeSet2(-INFLL, INFLL);
      }else{
        addRangeSet2(a, b);
      }
    }else{
      assert(false);
    }
  }
  
  auto ans = buildAnswerSet2(q);
  
  for(int f: ans)
    cout << p - f << endl;
  
  return 0;
}
