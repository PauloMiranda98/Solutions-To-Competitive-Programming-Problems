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
  int n;
  cin >> n;
  vector<queue<int>> q(2);
  for(int i=0; i<n; i++){
    int t, x;
    cin >> t >> x;
    q[x].push(t);
  }

  int t = 0;
  bool op = 0;

  while(!q[0].empty() or !q[1].empty()){
    if(q[op].size()){
      if(q[op].front() < t){
        int u = q[op].front();
        q[op].pop();
        t = max(u + 10, t);
      }else if(q[!op].size() and q[!op].front() < q[op].front()){
        op = !op;
        int u = q[op].front();
        q[op].pop();
        t = max(t, u) + 10;
      }else{
        int u = q[op].front();
        q[op].pop();
        t = max(u + 10, t);
      }
    }else{
      op = !op;
      int u = q[op].front();
      q[op].pop();
      t = max(t, u) + 10;
    }
  }
  cout << t << endl;
  return 0;
}
