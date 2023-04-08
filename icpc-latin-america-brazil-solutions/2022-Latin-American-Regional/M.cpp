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



const int MAXR = 1010;
const int MAXC = 110;

bitset<MAXC> mat[MAXR];

bool visited[MAXR][MAXC];
bitset<MAXC> piece[MAXC];

int r, c;

void preDfs(string s){
  memset(visited, 0, sizeof(visited));

  for(int r=0; r<c; r++){
    for(int i=0; i<c; i++){
      piece[r][i] = (s[(i+r)%c] == '1');    
    }
  } 
}

bool dfs(int i, int currRot){
  if(i == r + 1)
    return true;

  if(visited[i][currRot])
    return false;
  
  visited[i][currRot] = true;
  
  bool ans = false;
  
  int lRot = (c + currRot - 1)%c;
  if((mat[i] & piece[lRot]).none())
    ans |= dfs(i, lRot);
  
  int rRot = (currRot + 1)%c;
  if((mat[i] & piece[rRot]).none())
    ans |= dfs(i, rRot);
  
  if((mat[i+1] & piece[currRot]).none())
    ans |= dfs(i+1, currRot);

  if(i > 0 && (mat[i-1] & piece[currRot]).none())
    ans |= dfs(i-1, currRot);
  
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  cin >> r >> c;

  string s;
  cin >> s;
  
  mat[0] = bitset<MAXC>();
  
  for(int i=1; i<=r; i++){
    string line;
    cin >> line;
    
    mat[i] = bitset<MAXC>(line);
  }

  mat[r + 1] = bitset<MAXC>();
  
  bool ok = false;

  preDfs(s);
  ok |= dfs(0, 0);

  reverse(all(s));
  preDfs(s);
  ok |= dfs(0, 0);
  
  if(ok)
    cout << "Y" << endl;
  else
    cout << "N" << endl;
  
  return 0;
}
