#include <bits/stdc++.h>

using namespace std;

int main (){
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;
  
  string s;
  cin >> s;
  s += "b";
  
  int ans = 0, a = 0;
  
  for(char c: s){
    if(c == 'b'){
      if(a >= 2)
        ans += a;
      a = 0;
    }else{
      a++;
    }
  }
  
  cout << ans << endl;
}

// 0 0 1 1 0 1 0 1
// 0 0 1 9 0 1 0 1


