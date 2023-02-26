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
  
  set<char> st;

  for(char c: s)
    st.insert(c);
  
  map<int, int> f;
  
  for(char & c: s){
    if(f[c] == 0){
      f[c]++;
    }else{
      bool ok = false;
      
      for(char d='a'; d<='z'; d++){
        if(st.count(d) == 0){
          st.insert(d);
          c = d;
          ok = true;
          break;
        }
      }
      
      if(!ok){
        cout << "IMPOSSIBLE" << endl;
        return 0;
      }
    }
  }
  
  cout << s << endl;
  
  return 0;
}
