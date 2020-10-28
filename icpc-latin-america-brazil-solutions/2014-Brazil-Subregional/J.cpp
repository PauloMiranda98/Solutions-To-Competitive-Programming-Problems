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
typedef double ld;
struct Point2d{
  ld x, y;
};

const int MAXN = 210;
Point2d v[MAXN];

ld dp[MAXN][MAXN];
ld dist[MAXN][MAXN];

inline ld p2(ld x){
  return x*x;
} 

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  n = 2*n;
  for(int i=0; i<n; i++){
    cin >> v[i].x >> v[i].y;
  }
  for(int i=0; i<n-1; i++){
    dist[i][i] = dist[i][i+1] = 0;
    for(int j=i+2; j<n; j++){
      Point2d &a = v[i], &b = v[j];
      dist[i][j] = sqrt(p2(a.x-b.x) + p2(a.y-b.y));
    }
  }
  for(int sz=1; sz<=n; sz++){
    for(int i=0; i+sz<=n; i++){
      int j = i+sz-1;
      if(j-i+1 < 4){
        if(j-i == 1)
          dp[i][j] = 0;
        else
          dp[i][j] = 1e18;
      }else{
        ld ans = 1e18;
        for(int a=i+1; a<=j-2; a++)
          for(int b=a+1; b<=j-1; b++)
            ans = min(ans, dp[i][a] + dp[a][b] + dp[b][j] + dist[i][a] + dist[a][b] + dist[b][j]);
        dp[i][j] = ans;
      }
    }
  }
  cout << fixed << setprecision(4) << dp[0][n-1] << endl;
  return 0;
}
