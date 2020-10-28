#include <bits/stdc++.h>
#define F first
#define S second
#define endl '\n'
using namespace std;
const int MAXP = 10;
typedef pair<int, int> pii;
//This implementation considers the rotations as distinct
//              0, 10, 10+9, 10+9+8...
int pos[11] = {0, 10, 19, 27, 34, 40, 45, 49, 52, 54, 55};
struct Polyominoes{
  pii v[MAXP];
  int64_t id;
  int n;
  Polyominoes(){
    n = 1;
    v[0] = {0, 0};
    normalize();
  }
  Polyominoes(vector<pii> vp){
    n = vp.size();
    for(int i=0; i<n; i++)
      v[i] = vp[i];
    normalize();
  }
  pii& operator[](int i){
    return v[i];
  }
  bool add(int a, int b){
    for(int i=0; i<n; i++)
      if(v[i].F == a and v[i].S == b)
        return false;
    v[n++] = pii(a, b);
    normalize();
    return true; 
  }
  void normalize(){
    int mnx=100, mny=100;
    for(int i=0; i<n; i++)
      mnx = min(mnx, v[i].F), mny = min(mny, v[i].S);
    id = 0;
    for(int i=0; i<n; i++){
      v[i].F -= mnx, v[i].S -= mny;
      id |= (1LL<<(pos[v[i].F] + v[i].S));
    }
  }
  bool operator <(Polyominoes oth){
    return id < oth.id;
  }
};
vector<Polyominoes> polyominoes[MAXP+1];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
void buildPolyominoes(int mxN=10){
  for(int i=0; i<=mxN; i++)
    polyominoes[i].clear();
  Polyominoes init;
  queue<Polyominoes> q;
  unordered_set<int64_t> used;
  q.push(init);
  used.insert(init.id);
  while(!q.empty()){
    Polyominoes u = q.front(); q.pop();
    polyominoes[u.n].push_back(u);
    if(u.n == mxN)
      continue;
    for(int i=0; i<u.n; i++){
      for(int j=0; j<4; j++){
        Polyominoes to = u;
        bool ok = to.add(to[i].F + dx[j], to[i].S + dy[j]);
        if(ok and !used.count(to.id)){
          q.push(to);
          used.insert(to.id);
        }
      }
    }
  }
}
int mat[50][50];
int n, m;
typedef long long ll;
int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(NULL);
  
  cin >> n >> m;
  buildPolyominoes(m);
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      cin >> mat[i][j];
  int ans = 0;
  for(Polyominoes &p: polyominoes[m]){
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        int aux = 0;
        for(int k=0; k<m; k++){
          int a = i+p[k].F, b = j+p[k].S;
          if(a<n and b<n)
            aux += mat[a][b];
        }
        if(aux > ans)
          ans = aux;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
