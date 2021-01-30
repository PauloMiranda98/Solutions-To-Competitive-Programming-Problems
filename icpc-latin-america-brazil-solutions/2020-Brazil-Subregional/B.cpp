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
bool mat[12][12];
bool isValid(int i, int j){
  return i>=1 and i<=10 and j>=1 and j<=10 and !mat[i][j];
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  char ans = 'Y';
  int n;
  cin >> n;
  for(int i=0; i<n; i++){
    int d, l, r, c;
    cin >> d >> l >> r >> c;
    if(d == 0){
      for(int j=0; j<l; j++){
        if(!isValid(r, c+j))
          ans = 'N';
        else
          mat[r][c+j] = true;
      }
    }else{
      for(int j=0; j<l; j++){
        if(!isValid(r+j, c))
          ans = 'N';
        else
          mat[r+j][c] = true;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
