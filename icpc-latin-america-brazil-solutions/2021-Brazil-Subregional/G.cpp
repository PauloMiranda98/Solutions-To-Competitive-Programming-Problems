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

const int MAXN = 80;
ll v[MAXN];
string ans;
void solve(ll n, int i){
  if(n == 1){
    cout << ans << endl;
    exit(0);
    return;
  }
  if(v[i] == 1)
    return;

  if(n % v[i] == 0){
    for(int j = 0; j < i-1; j++)
     ans += 'A';
    ans += 'B';

    solve(n/v[i], i);
    for(int j = 0; j < i; j++){
      ans.pop_back();
    }
  }

  solve(n, i-1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int last = 0;
  ll n;
  cin >> n;

  v[0] = v[1] = 1;
  for(int i = 2; v[i-1] + v[i-2] <= 1000000000000000ll; i++){
    v[i] = v[i-1] + v[i-2];
    last = i;
  }
  solve(n, last);
  cout << "IMPOSSIBLE" << endl;
  return 0;
}
