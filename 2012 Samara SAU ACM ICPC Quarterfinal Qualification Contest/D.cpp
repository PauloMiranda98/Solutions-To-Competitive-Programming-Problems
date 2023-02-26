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

const int MAXN = 1000010;

ll dp[MAXN];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int n;
  cin >> n;
  
  dp[1] = 1;
  
  for(int i=1; i<=n; i++){
    for(int j=i+i; j<=n; j+=i)
      dp[j] += dp[i];
  }
  
  cout << dp[n] << endl;
  
  return 0;
}
