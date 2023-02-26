#include <bits/stdc++.h>
#define T first
#define C second
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

const int MAXN = 2000010;

int nx[2*MAXN + 2];

int find(int x){
  if(nx[x] == -1)
    return x;

  return nx[x] = find(nx[x]);
}

void use(int x){
  nx[x] = x-1;
}

vector<int> test(int cost, vector<pii> &v){
  int n = (int)v.size();
  vector<int> ans(n);
  
  memset(nx, -1, sizeof(nx));
  
  for(int i=n-1; i>=0; i--){
    auto [t, c] = v[i];
    
    int mx = cost - c;
    
    int p = find(min(t + mx, 2*MAXN));
    
    if(p < t)
      return {};

    use(p);

    ans[i] = p;
  }
  
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int n;
  cin >> n;
  vector<pii> v(n);
  
  int mxC = 0;
  for(int i=0; i<n; i++){
    cin >> v[i].T >> v[i].C;
    mxC = max(mxC, v[i].C);
  }
  
  int lo = mxC, hi = mxC + n + 1;
  int ans = hi;
  
  while(lo <= hi){
    int mid = (lo + hi)/2;
    
    if(test(mid, v).size() > 0){
      ans = mid;
      hi = mid - 1;
    }else{
      lo = mid + 1;
    }
  }
  
  vector<int> ret = test(ans, v);
  
  for(int x: ret)
    cout << x << " ";
  cout << endl;
  
  return 0;
}
