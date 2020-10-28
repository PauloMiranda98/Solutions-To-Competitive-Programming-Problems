#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, m;
  cin >> n >> m;
  int ans = 0;
  for(int i=0; i<n; i++){
    int cnt = 0;
    for(int j=0; j<m; j++){
      int x;
      cin >> x;
      cnt += (x>0);
    }
    if(cnt == m)
      ans++;
  }
  cout << ans << endl;
  return 0;
}
