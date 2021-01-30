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

  string s;
  cin >> s;
  int p[2] = {0, 0};
  int g[2] = {0, 0};
  bool curr = 0;
  for(char c: s){
    if(c == 'S'){
      p[curr]++;
    }else if(c == 'R'){
      curr = !curr;
      p[curr]++;
    }else{
      if(max(g[0], g[1]) == 2){
        cout << g[0];
        if(curr == 0)
          cout << " (winner)";
        cout << " - ";
        cout << g[1];
        if(curr == 1)
          cout << " (winner)";
        cout << endl;
      }else{
        cout << g[0] << " (" << p[0] << ((curr==0)?"*)":")");
        cout << " - ";
        cout << g[1] << " (" << p[1] << ((curr==1)?"*)":")");
        cout << endl;
      }
    }
    int mx = max(p[0], p[1]);
    if((mx >= 5 and abs(p[0]-p[1]) >= 2) or mx >= 10){
      if(p[0] > p[1]){
        g[0]++;
        curr = 0;
      }else{
        g[1]++;
        curr = 1;
      }
      p[0] = p[1] = 0;
    }
  }
  return 0;
}
