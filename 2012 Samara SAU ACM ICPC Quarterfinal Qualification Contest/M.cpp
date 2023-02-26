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

const int MAXN = 200010;

int last[MAXN];
int color[MAXN];
int dp[MAXN];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  
  
  for(int i=0; i<n; i++)
    cin >> color[i];
  
  memset(last, -1, sizeof(last));
  
  dp[n-1] = 0;
  last[color[n-1]] = n-1;
    
  for(int i=n-2; i>=0; i--){
    dp[i] = dp[i+1] + 1;
    
    int c = color[i];
    
    if(last[c] != -1){
      dp[i] = min(dp[i], dp[last[c]] + 1);
    }
    
    last[c] = i;
  }
  
  cout << dp[0] << endl;
  
  return 0;
}
