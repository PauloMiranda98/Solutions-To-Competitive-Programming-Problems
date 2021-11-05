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
  int n, k;
  cin >> n >> k;
  vector<vector<int>> v0(k);
  vector<vector<int>> v1(k);
  for(int i=0; i<n; i++){
    int x, c;
    cin >> x >> c;
    v0[c-1].emplace_back(i);
    v1[c-1].emplace_back(x);
  }
  vector<int> ans(n);
  for(int i=0; i<k; i++){
    sort(all(v0[i]));
    sort(all(v1[i]));
    int m = v0[i].size();
    for(int j=0; j<m; j++){
      ans[v0[i][j]] = v1[i][j];
    }
  }
  if(is_sorted(all(ans)))
    cout << "Y" << endl;
  else
    cout << "N" << endl;

  return 0;
}
