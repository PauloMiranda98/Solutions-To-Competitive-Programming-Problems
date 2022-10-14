#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define endl '\n'
 
using namespace std;
 
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using ppp = pair<pii, pii>;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};


map<ppp, vector<int>> edges;

void add(int a, int b, int c, int d, int id){
  pii p1(a, b);
  pii p2(c, d);

  if(p1 > p2)
    swap(p1, p2);
  
  edges[ppp(p1, p2)].push_back(id);
}

ld dist(int a, int b, int c, int d){
  ld x = a - c;
  ld y = b - d;
  
  return sqrtl(x*x + y*y);
}

ld getArea(ld a, ld b, ld c){
  ld s = (a + b + c)/2;
  return sqrtl(s*(s-a)*(s-b)*(s-c));
}

const int MAXN = 100010;

ld area[MAXN];
vector<int> adj[MAXN];

bool calc[MAXN][2];
ld dp[MAXN][2];

ld solve(int u, int p, bool used){
  if(calc[u][used])
    return dp[u][used];
  
  ld op1 = area[u];
  ld op2 = 0;
  
  for(int to: adj[u]) if(to != p){
    op1 += solve(to, u, true);
    op2 += solve(to, u, false);
  }
  if(adj[u].size() == 3 and !used){
    dp[u][used] = max(op1, op2);
  }else{
    dp[u][used] = op2;
  }
  calc[u][used] = true;
  return dp[u][used];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int n;
  cin >> n;
  
  long double total = 0;
  
  for(int i=0; i<n; i++){
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    
    add(a, b, c, d, i);
    add(a, b, e, f, i);
    add(c, d, e, f, i);

    area[i] = getArea(dist(a, b, c, d), dist(a, b, e, f), dist(c, d, e, f));
    total += area[i];
  }
  
  for(auto [_, v]: edges){
    if(v.size() == 2){
      int a = v[0];
      int b = v[1];

      adj[a].push_back(b);
      adj[b].push_back(a);
    }
  }
  
  ld ans = total - solve(0, -1, false);
  
  cout << fixed << setprecision(1) << ans << endl;
  
  return 0;
}
