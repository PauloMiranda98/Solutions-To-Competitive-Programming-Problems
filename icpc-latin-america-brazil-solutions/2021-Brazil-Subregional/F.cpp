#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define endl '\n'
 
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int dx[] = { 0, 0, -1, 1};
const int dy[] = {-1, 1,  0, 0};


using namespace std;
typedef pair<int, int> pii; 
#define X first
#define Y second

struct Polygon{
  vector<pii> v;
  Polygon(){}
  Polygon(vector<pii> v0): v(v0){}
};
// tuple<x0, y0, operation, x1, y1, id, side>
typedef tuple<int, int, int, int, int, int, bool> tp;

const int BEGIN_POLYGON = 1;
const int BEGIN_SEGMENT = 2;
const int END_SEGMENT = 3;
const bool UP = false;
const bool DOWN = true;

//- There is no intersection between the polygons
//- The parent of Polygon i will be the smallest polygon that includes i
namespace PolygonsToTree{
  int POS_X = 0;
  int n;
  vector<Polygon> vc;  
  vector<int> p;
  struct SetElement{
    int x0, y0;
    double k;
    int id;
    bool side;
    SetElement(int ax, int ay, int bx, int by, int id0, bool s): x0(ax), y0(ay), id(id0), side(s){
      k = (by - ay)/double(bx - ax);
    };
    double getY(int x = POS_X) const{
      double Y = y0 + k*(x - x0);
      return Y;
    }
    bool operator <(const SetElement &o) const{
      auto l = getY(), r = o.getY();
      if(abs(l-r) < 1e-9){
        if(abs(k-o.k) < 1e-9)
          return side > o.side;
        else
          return k < o.k;
      }else{
        return l < r;
      }
    }
  };
  void updateParent(int id, int par){
    if(par != -1 and p[id] == -1) p[id] = par; 
  }
//Public
  vector<vector<int>> solve(vector<Polygon> polygons){
    n = polygons.size();
    p.assign(n, -1);
    vector<vector<int>> adj(n, vector<int>());
    vector<tp> events;
    for(int i=0; i<n; i++){
      auto v = polygons[i].v;
      int m = v.size();
      v.push_back(v.front());
      int mnX=INF, y=INF;
      for(int j=0; j<m; j++){
        auto a = v[j], b = v[j+1];
        bool side = (v[j+1].X - v[j].X) < 0;
        if(a.X > b.X)
          swap(a, b);
        if(a.X == b.X)
          continue;
        if(a.X < mnX or (a.X == mnX and a.Y < y)){
          mnX = a.X;
          y = a.Y;
        }
        
        events.emplace_back(a.X, a.Y, BEGIN_SEGMENT, b.X, b.Y, i, side);
        events.emplace_back(b.X, b.Y, END_SEGMENT, a.X, a.Y, i, side);
      }
      events.emplace_back(mnX, y, BEGIN_POLYGON, 0, 0, i, false);
    }
    sort(events.begin(), events.end());
    set<SetElement> st;

    for(auto [x0, y0, op, x1, y1, id, side]: events){
      POS_X = x0;

      if(op == BEGIN_POLYGON){
        auto it = st.lower_bound(SetElement(x0, y0, x0+1, y0, id, false));        

        if(it != st.begin()){
          it--;

          int id2 = it->id;
          if(it->side == UP) 
            updateParent(id, id2);
          else
            updateParent(id, p[id2]);
        }
        if(p[id] != -1){
          adj[p[id]].push_back(id);
        }
      }else if(op == BEGIN_SEGMENT){
        st.insert(SetElement(x0, y0, x1, y1, id, side));
      }else if(op == END_SEGMENT){
        st.erase(SetElement(x1, y1, x0, y0, id, side));
      }else{
        assert(false);
      }
    }
    return adj;
  }
};

const int MAXN = 200010;
int dp[MAXN];
vector<vector<int>> adj;

int solve(int u, int d){
  int ans = 0;
  dp[u] = 0;
  int mx1 = 0, mx2 = 0;
  for(int to: adj[u]){
    int x = solve(to, d + 1);
    dp[u] = max(dp[u], dp[to] + 1);

    if(dp[to] + 1 >= mx1){
      mx2 = mx1;
      mx1 = dp[to] + 1;
    }else if(dp[to] + 1 > mx2){
      mx2 = dp[to] + 1;
    }

    ans = max(ans, x);
  }
  ans = max(ans, 2*mx1 + mx2 + d);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  vector<Polygon> polygons;
  
  for(int i=0; i<n; i++){
    int m;
    cin >> m;

    vector<pii> v(m);
    for(int j=0; j<m; j++){
      auto &[x, y] = v[j];
      cin >> x >> y;
    }
    polygons.push_back(Polygon(v));
  }
  adj = PolygonsToTree::solve(polygons);

  adj.push_back({});
  for(int i=0; i<n; i++){
    if(PolygonsToTree::p[i] == -1)
      adj[n].push_back(i);
  }
  cout << solve(n, 0) << endl;
  
  return 0;
}
