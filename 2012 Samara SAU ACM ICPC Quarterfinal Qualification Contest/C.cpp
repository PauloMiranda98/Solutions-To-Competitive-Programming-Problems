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

const int MAXN = 310;
int d[MAXN][MAXN];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> d[i][j];
    }
  }
  
  for(int k=0; k<n; k++){
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        if(d[i][k] + d[k][j] < d[i][j]){
          cout << -1 << endl;
          return 0;
        }
      }
    }
  }
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cout << d[i][j] << " ";
    }
    cout << endl;
  }
  
  return 0;
}
