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

const int MAXN = 2510;

char mat[MAXN][MAXN];

int up[MAXN][MAXN];
int left2[MAXN][MAXN];

int getUp(int j, int l, int r){
  return up[r][j] - up[l-1][j];
}

int getLeft(int i, int l, int r){
  return left2[i][r] - left2[i][l-1];
}

void build(){
  int n, m;
  cin >> n >> m;
  
  for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
      cin >> mat[i][j];
  
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      int sum = (mat[i][j] == '#');
      
      up[i][j] = up[i-1][j] + sum;
      left2[i][j] = left2[i][j-1] + sum;
    }
  }
}

bool canGo(int x1, int y1, int x2, int y2){
  if(x1 == x2)
    return getLeft(x1, min(y1, y2), max(y1, y2)) == 0;
  else if(y1 == y2)
    return getUp(y1, min(x1, x2), max(x1, x2)) == 0;
  else
    return false;
}

bool trySolve(int x, int y, int x1, int y1, int x2, int y2){
  
  return canGo(x, y, x1, y1) and canGo(x, y, x2, y2);
}

bool solve(int x1, int y1, int x2, int y2){
  return trySolve(min(x1, x2), min(y1, y2), x1, y1, x2, y2) 
    or trySolve(min(x1, x2), max(y1, y2), x1, y1, x2, y2)
    or trySolve(max(x1, x2), min(y1, y2), x1, y1, x2, y2)
    or trySolve(max(x1, x2), max(y1, y2), x1, y1, x2, y2);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  build();
  
  int q;
  cin >> q;
  
  for(int i=0; i<q; i++){
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << (solve(x1, y1, x2, y2) ? "YES" : "NO") << endl;
  }
  
  return 0;
}
