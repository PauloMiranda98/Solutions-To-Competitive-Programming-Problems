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
ll dp[52][52];
ll comb(int n, int k){
  if(n < k)
    return 0;
  if(n == k or k == 0)
    return 1;
  if(dp[n][k] != -1)
    return dp[n][k];
  return dp[n][k] = comb(n-1, k-1) + comb(n-1, k);
}
int n;
ll v[50];
ll solve(int i, int k, ll sum){
  if(k < 0)
    return 0;
  if(i == n)
    return k==0;
  int m = n-i-1; 
  if(v[i] <= sum)
    return comb(m, k) + solve(i+1, k-1, sum - v[i]);
  else
    return solve(i+1, k, sum);
}
int main() {
  memset(dp, -1, sizeof(dp));
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int k;
  cin >> n >> k;
  for(int i=0; i<n; i++){
    cin >> v[i];
  }
  sort(v, v+n, greater<ll>());
  ll a, b;
  cin >> a >> b;
  cout << solve(0, k, b) - solve(0, k, a-1) << endl;
  return 0;
}
