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

typedef long double ld;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, a, b;
  cin >> n >> a >> b;
  vector<ld> E(n+1);
  if(a > 0){
    E[0] = 0;
    ld sum = 0;
    for(int i=1; i<=n; i++){
      if(i-a >= 0)
        sum += E[i-a];
      if(i-b-1 >= 0)
        sum -= E[i-b-1];
      E[i] = sum/(b-a+1) + 1;
    }
    cout << fixed << setprecision(12) << E[n] << endl;
  }else{
    E[0] = 0;
    ld sum = 0;
    for(int i=1; i<=n; i++){
      sum += E[i-1];
      if(i-b-1 >= 0)
        sum -= E[i-b-1];
      E[i] = sum/b + (b+1)/(ld)b;
    }
    cout << fixed << setprecision(12) << E[n] << endl;
  }
  
  return 0;
}
