#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main (){
  ios_base::sync_with_stdio(0);
  
  int n, C;
  cin >> n >> C;
  
  unordered_map<string, int> st;
    
  for(int i=0; i<n; i++){
    string s;
    cin >> s;
    
    int p = -1;
    for(int j=0; j<C; j++){
      if(s[j] == '*')
        p = j;
    }

    for(char c='a'; c <= 'z'; c++){
      s[p] = c;
      st[s]++;
    }
  }
  
  pair<int, string> ans(-1, "");
  for(auto [s, f]: st){
    if(f > ans.first){
      ans = make_pair(f, s);
    }else if(f == ans.first and s < ans.second){
      ans = make_pair(f, s);
    }
  }
  
  cout << ans.second << " " << ans.first << endl;

  return 0;
}

/*
5 4
rat*
ru*d
rot*
r*ta
r*ta


5 4
bon*
fon*
n*no
*eto
*ano
*/


