#include <bits/stdc++.h>
#define F first
#define S second
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

int mat[MAXN][MAXN];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int k;
  cin >> k;
  
  if(k == 1){
    cout << 0 << endl;
    return 0;
  }

  if(k == 2){
    cout << 1 << endl;
    cout << "1 1 1" << endl;

    return 0;
  }

  
  int ans = 0;
  
  while((1<<ans) < k){
    ans++;
  }
  
  int mask = (1<<ans) - 1;
  for(int i=0; i<MAXN; i++){
    for(int j=0; j<MAXN; j++){
      if(i == 0 or j%3 == 0)
        mat[i][j] = mask;
    }
  }
  
  k -= 2;
  
  for(int i=0; i<MAXN; i++){
    for(int j=0; j<MAXN; j++){
      if(mat[i][j] == 0 and k > 0){
        mat[i][j] = --mask;
        k--;
      }
    }
  }
  
  assert(k == 0);
  
  cout << ans << endl;
  
  for(int b=0; b<ans; b++){
    vector<pii> v;
    for(int i=0; i<MAXN; i++){
      for(int j=0; j<MAXN; j++){
        if(mat[i][j] & (1<<b))
          v.emplace_back(i, j);
      }
    }
    cout << v.size();
    for(auto [x, y]: v)
      cout << " " << x+1 << " " << y+1;
    cout << endl;
  }
  
  return 0;
}
