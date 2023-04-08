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


const int MAXN = 102;
int mat[MAXN][MAXN];
pii pos[MAXN*MAXN];
bool used[MAXN*MAXN];
int n, m;

int bfs(int from){
  memset(used, 0, sizeof(used));
  used[from] = true;

  int ans = 0;
  int last = 0;
  for(int id=1; id<=n*m; id++){
    auto [x, y] = pos[id];
    
    if(id < last or !used[id])
      continue;

    ans++;
    last = id;
    
    for(int k=0; k<4; k++){
      int nx = x + dx[k];
      int ny = y + dy[k];
      if(mat[nx][ny] > id and !used[mat[nx][ny]]){
        used[mat[nx][ny]] = true;
      }
    }
    
  }
  
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  cin >> n >> m;

  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      int x;
      cin >> x;
      
      mat[i][j] = x;
      pos[x] = pii(i, j);
    }
  }

  int ans = 0;
  for(int i=1; i<=n*m; i++)
    ans = max(ans, bfs(i));
  
  cout << ans << endl;
  return 0;
}
