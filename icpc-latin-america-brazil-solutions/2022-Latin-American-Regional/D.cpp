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
  int n, a, b;
  cin >> n >> a >> b;
  
  for(int i=0; i<n; i++){
    char h, w;
    cin >> h >> w;
    if(h == 'Y' or b == 0){
      a--;
      b++;
      cout << "Y ";
    }else{
      cout << "N ";      
    }

    if(w == 'Y' or a == 0){
      a++;
      b--;
      cout << "Y\n";
    }else{
      cout << "N\n";      
    }
  }
  return 0;
}
