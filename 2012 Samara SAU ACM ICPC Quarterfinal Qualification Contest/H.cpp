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


const int MAXN = 100;
int used[MAXN], T;

int mex(){
  for(int i=0; ; i++)
    if(used[i] != T)
      return i;
  
  return -1;
}

int g[MAXN];

void build(){
  g[1] = 0;
  
  for(int i=2; i<MAXN; i++){
    T++;
    
    for(int j=i-1; 2*j>=i; j--){
      used[g[j]] = T;
    }
    
    g[i] = mex();
    cout << i << ": " << g[i] << endl;
  }
}

bool grundyNumberIsZero(int x){
  return (x & (x+1)) == 0;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
//  build();
  int n;
  cin >> n;
  
  vector<int> v(n);
  for(int i=0; i<n; i++){
    cin >> v[i];
  }
  
  int mx = *max_element(all(v));
  
  if(grundyNumberIsZero(mx)){
    cout << "Mike" << endl;
  }else{
    cout << "Constantine" << endl;
  }

  return 0;
}
