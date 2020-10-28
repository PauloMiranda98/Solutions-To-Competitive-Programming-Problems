#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int x, y;
  cin >> x >> y;
  cout << (x + (y-x)-1)/(y-x) + 1 << endl;
  return 0;
}
