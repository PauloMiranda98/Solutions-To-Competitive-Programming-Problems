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

int dp[10][1010][1010];
int n, k, e;

int solve(int a, int b, int i){
  if(i == 0)
    return a + b;
  
  if(dp[a][b][i] != -1)
    return dp[a][b][i];

  if(i == k)
    return dp[a][b][i] = solve(a, b, i - 1);
  
  int ans = solve(a, b, i - 1);
  
  if(i <= a)
    ans = min(ans, solve(a - i, b, i - 1));
  if(i <= b)
    ans = min(ans, solve(a, b - i, i - 1));

  return dp[a][b][i] = ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> k >> e;
  
  int a = e;
  int b = n - k - e;
  
  if(min(a, b) >= 10){
    cout << 0 << endl;
    return 0;
  }
  
  memset(dp, -1, sizeof(dp));
  cout << solve(min(a, b), max(a, b), n) << endl;
  
  return 0;
}
