#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define endl '\n'
using namespace std;

typedef pair<int, int> pii;
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
const int dx[] = { 0, 0, -1, 1};
const int dy[] = {-1, 1,  0, 0};

char mat[MAXN][MAXN];
bool seen[MAXN][MAXN];
int dist[MAXN][MAXN];
int bfs(int n){
  if(seen[1][1])
    return INF;
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      dist[i][j] = INF;
  queue<pii> q;
  q.push(pii(1, 1));
  dist[1][1] = 1;
  seen[1][1] = true;
  while(!q.empty()){
    pii u = q.front(); q.pop();
    for(int k=0; k<4; k++){
      pii to(u.F + dx[k], u.S + dy[k]);
      if(!seen[to.F][to.S]){
        dist[to.F][to.S] = dist[u.F][u.S] + 1;
        seen[to.F][to.S] = true;
        q.push(to);
      }
    }
  }
  return dist[n][n];
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      cin >> mat[i][j];
  int ans = INF;
  for(int mask=0; mask<(1<<10); mask++){
    for(int i=0;i<=n+1; i++)
      for(int j=0; j<=n+1; j++)
        seen[i][j] = true;
    for(int i=1; i<=n; i++){
      for(int j=1; j<=n; j++){
        char &c = mat[i][j];
        if(c >= 'a' and c <= 'j' and ((mask>>(c-'a'))&1))
          seen[i][j] = false;
        if(c >= 'A' and c <= 'J' and (((mask>>(c-'A'))&1)==0))
          seen[i][j] = false;
      }
    }
    ans = min(ans, bfs(n));
  }
  if(ans == INF)
    cout << -1 << endl;
  else
    cout << ans << endl;
  return 0;
}
