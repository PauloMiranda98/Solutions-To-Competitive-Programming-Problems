#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 2002;

int matLR[MAXN + 2][MAXN + 2];
int matUD[MAXN + 2][MAXN + 2];
int mat[MAXN + 2][MAXN + 2];

int dx[] = {0, 0, -1, +1};
int dy[] = {-1, +1, 0, 0};

int ID = 5;

int bfs(int i, int j){
  if(mat[i][j])
    return 0;
  
  ID++;
  
  queue<pii> q;
  q.emplace(i, j);
  mat[i][j] = ID;

  int ans = 0;
  while(!q.empty()){
    i = q.front().first;
    j = q.front().second;
    q.pop();
    ans++;
    
    for(int k=0; k<4; k++){
      int a = i + dx[k];
      int b = j + dy[k];
    
      if(a >= 0 and a < MAXN and b >= 0 and b < MAXN and mat[a][b] == 0){
        mat[a][b] = ID;
        q.emplace(a, b);
        
        if(mat[a+1][b] != 0 and mat[a+1][b] != ID){
          ans++;
          mat[a+1][b] = ID;
        }
        if(mat[a][b+1] != 0 and mat[a][b+1] != ID){
          ans++;
          mat[a][b+1] = ID;
        }
        if(mat[a+1][b+1] != 0 and mat[a+1][b+1] != ID){
          ans++;
          mat[a+1][b+1] = ID;
        }
      }
    }
  }
        
  return ans;
}

int main (){
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;

  int x0, y0;
  cin >> x0 >> y0;
  x0 *= 2;
  y0 *= 2;
  
  int x1 = x0, y1 = y0;
  
  for(int i=0; i<n; i++){
    int x, y;
    cin >> x >> y;

    x *= 2;
    y *= 2;
    
    if(x == x1){
      int l = min(y, y1);
      int r = max(y, y1);
      
      matLR[x][l] += 1;
      matLR[x][r+1] -= 1;
    }else if(y == y1){
      int l = min(x, x1);
      int r = max(x, x1);
      matUD[l][y] += 1;
      matUD[r+1][y] -= 1;
    }else{
      assert(false);
    }
    x1 = x;
    y1 = y;
  }
  
  for(int i=0; i<MAXN; i++){
    for(int j=1; j<MAXN; j++){
      matLR[i][j] += matLR[i][j-1];  
    }
  }

  for(int j=0; j<MAXN; j++){
    for(int i=1; i<MAXN; i++){
      matUD[i][j] += matUD[i-1][j];  
    }
  }
  
  for(int i=0; i<MAXN; i++){
    for(int j=0; j<MAXN; j++){
      mat[i][j] = (matLR[i][j] + matUD[i][j]) != 0;  
    }
  }
  
  bfs(0, 0);
  
  int ans = 0;
  
  for(int i=0; i<MAXN; i++){
    for(int j=0; j<MAXN; j++){
      int x = bfs(i, j);
      
      ans = max(ans, x);
    }
  }
  
  cout << ans/4 << endl;
  
  return 0;
}


/*
8
2 1
7 1
7 4
3 4
3 2
5 2
5 6
2 6
2 1

14
1 1
8 1
8 6
6 6
6 2
2 2
2 4
7 4
7 5
3 5
3 3
4 3
4 6
1 6
1 1
*/



