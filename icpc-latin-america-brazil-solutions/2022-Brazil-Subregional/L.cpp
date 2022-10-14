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

int freq[MAXN], color[MAXN];
ll ans[MAXN];

struct Data{
  ll sum;
  map<int, int> mp;

  Data(){
    sum = 0;
  }
  
  void addColor(int c, int f){
    ll a = mp[c];
    ll b = freq[c] - a;
    sum -= a*b;
    
    mp[c] += f;
    
    a = mp[c];
    b = freq[c] - a;
    sum += a*b;
  }
};


vector<pii> adj[MAXN];

void merge(Data &to, Data &from){
  if(to.mp.size() < from.mp.size())
    swap(to, from);

  for(auto [c, f]: from.mp)
    to.addColor(c, f);
}

void dfs(int u, int id, Data &curr){
  for(auto [to, edgeId]: adj[u]) if(edgeId != id){
    Data d;

    dfs(to, edgeId, d);
    merge(curr, d);
  }
  
  curr.addColor(color[u], 1);
  ans[id] = curr.sum;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int n;
  cin >> n;
  
  for(int i=1; i<=n; i++){
    cin >> color[i];

    freq[color[i]]++;
  }
  
  for(int i=1; i<=n-1; i++){
    int a, b;
    cin >> a >> b;
    
    adj[a].emplace_back(b, i);
    adj[b].emplace_back(a, i);
  }
  
  Data d;
  
  dfs(1, 0, d);
  
  for(int i=1; i<=n-1; i++)
    cout << ans[i] << " ";
  
  cout << endl;

  return 0;
}
