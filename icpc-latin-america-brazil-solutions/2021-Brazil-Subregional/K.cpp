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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t, d, m;
  cin >> t >> d >> m;
  vector<int> v;
  v.push_back(0);
  for(int i=0; i<m; i++){
    int x;
    cin >> x;
    v.push_back(x);
  }
  v.push_back(d);
  m += 2;
  for(int i=1; i<m; i++){
    if(v[i]-v[i-1] >= t){
      cout << "Y" << endl;
      return 0;
    }
  }
  cout << "N" << endl;
  return 0;
}
