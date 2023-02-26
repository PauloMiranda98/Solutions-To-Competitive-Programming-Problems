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

const int MAXN = 200010;
int l[MAXN], r[MAXN];
int d[MAXN], p[MAXN];

set<int> st;

void build(){
  memset(l, -1, sizeof(l));
  memset(r, -1, sizeof(r));
  memset(p, -1, sizeof(p));
  memset(d, 0x3f, sizeof(d));

  st.insert(0);
  d[0] = 0;
}

int add(int x){
  st.insert(x);
  
  { // is right?
    auto it = st.find(x);
    it++;
    if(it != st.end()){
      int y = *it;
      
      if(l[y] == -1){
        l[y] = x;
        p[x] = y;
        
        d[x] = d[y] + 1;
      }
    }
  }

  { // is left?
    auto it = st.find(x);
    
    if(it != st.begin()){
      it--;
      int y = *it;
      
      if(r[y] == -1){
        r[y] = x;
        p[x] = y;
        
        d[x] = d[y] + 1;
      }
    }
  }
  
  assert(d[x] != -1);
  
  return d[x];
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);


  int n;
  cin >> n;

  build();
  ll ans = 0;
  for(int i=0; i<n; i++){
    int x;
    cin >> x;
    
    int dx = add(x) - 1;
    //cout << x << ":" << dx << endl;

    ans += dx;
  }
  
  cout << ans << endl;
  
  return 0;
}
