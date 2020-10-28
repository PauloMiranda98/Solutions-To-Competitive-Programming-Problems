#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
const int MAXM = 500;
typedef long long ll;
struct Plane{
  int a, b, c, d;
};

Plane v[MAXM];
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int m, n;
  cin >> m >> n;
  for(int i=0; i<m; i++)
    cin >> v[i].a >> v[i].b >> v[i].c >> v[i].d;

  unordered_map<bitset<MAXM>, int> f;  
  for(int i=0; i<n; i++){
    int x, y, z;
    cin >> x >> y >> z;
    bitset<MAXM> bs;
    for(int j=0; j<m; j++){
      int aux = v[j].a*x + v[j].b*y + v[j].c*z - v[j].d;
      bs[j] = (aux > 0);
    }
    f[bs]++;
  }
  int ans = 0;
  for(auto p: f){
    ans = max(ans, p.second);
  }
  cout << ans << endl;
  return 0;
}
