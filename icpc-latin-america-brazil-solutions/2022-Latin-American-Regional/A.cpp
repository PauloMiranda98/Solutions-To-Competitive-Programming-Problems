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

const int MAXN = 1010;
vector<int> adj[MAXN], rev[MAXN];
int n;

vector<bool> bfs(int source, int ignore){
  assert(source != ignore);

  vector<bool> used(n, false);

  queue<int> q;
  q.push(source);
  used[source] = true;
  
  while(!q.empty()){
    int u = q.front();
    q.pop();
    
    for(int to: rev[u]) if(!used[to] && to != ignore){
      q.push(to);
      used[to] = true;
    }
  }
  
  return used;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  
  for(int i=0; i<n; i++){
    int a, b;
    cin >> a >> b;
    a--; b--;

    adj[i].push_back(a);
    adj[i].push_back(b);
    
    rev[a].push_back(i);
    rev[b].push_back(i);
  }
  
  for(int i=0; i<n; i++){
    auto a = adj[i][0];
    auto b = adj[i][1];
    
    auto ui = bfs(i, -1);
    auto ua = bfs(a, i);
    auto ub = bfs(b, i);
    
    bool ok = false;
    for(int j=0; j<n; j++){
      if(j != i and ui[j] && ua[j] && ub[j])
        ok = true;
    }
    if(ok) cout << "Y";
    else cout << "N";
  }
  cout << endl;
  
  return 0;
}
