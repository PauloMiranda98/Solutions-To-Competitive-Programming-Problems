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
const int MAXL = 42;
char mat[MAXL][MAXL];
set<int> f[MAXL][MAXL];
int n, m;
void test(map<char, int> &mp, vector<pii> &v, int id){
  map<char, int> aux;
  for(pii p: v)
    aux[mat[p.F][p.S]]++;
  if(aux == mp)
    for(pii p: v)
      f[p.F][p.S].insert(id);
}
void solve(string s, int id){
  map<char, int> mp;
  for(char c: s)
    mp[c]++;
  int k = s.size();
  for(int i=1; i<=n; i++){
    for(int j=1; j+k-1<=m; j++){
      vector<pii> v;
      for(int a=0; a<k; a++)
        v.emplace_back(i, j+a);
      test(mp, v, id);
    }
  }
  for(int j=1; j<=m; j++){
    for(int i=1; i+k-1<=n; i++){
      vector<pii> v;
      for(int a=0; a<k; a++)
        v.emplace_back(i+a, j);
      test(mp, v, id);
    }
  }
  for(int i=1; i+k-1<=n; i++){
    for(int j=1; j+k-1<=m; j++){
      vector<pii> v;
      for(int a=0; a<k; a++)
        v.emplace_back(i+a, j+a);
      test(mp, v, id);
    }
  }
  for(int i=1; i+k-1<=n; i++){
    for(int j=k; j<=m; j++){
      vector<pii> v;
      for(int a=0; a<k; a++)
        v.emplace_back(i+a, j-a);
      test(mp, v, id);
    }
  }

}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
      cin >> mat[i][j];
  int k;
  cin >> k;
  for(int i=0; i<k; i++){
    string s;
    cin >> s;
    solve(s, i);
  }
  int ans = 0;
  for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
       ans += (f[i][j].size() >= 2);
  cout << ans << endl;
  return 0;
}
