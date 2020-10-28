#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  n /= 2;
  int ans=1, pos=2;
  while(pos != 1){
    if(pos <= n)
      pos += pos;
    else
      pos -= (2*n-pos+1);
    ans++;
  }
  cout << ans << endl;
  return 0;
}
