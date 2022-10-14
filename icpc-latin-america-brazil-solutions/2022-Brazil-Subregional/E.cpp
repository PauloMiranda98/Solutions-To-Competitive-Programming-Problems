#include <bits/stdc++.h>

using namespace std;

set<int> pos[1000010];

int main (){
  ios_base::sync_with_stdio(0);
  
  int n;
  cin >> n;
  vector<int> v(n);
  
  for(int i=0; i<n; i++){
    cin >> v[i];
    pos[v[i]].insert(i);
  }
  
  int ans = 0;
  for(int i=0; i<n; i++){
    if(v[i] != -1){
      int x = v[i];
      int j = i;
      pos[x].erase(i);
      
      while(true){
        x--;
        auto it = pos[x].upper_bound(j);
        if(it == pos[x].end())
          break;
          
        j = *it;
        v[j] = -1;
        pos[x].erase(it);
      }
      
      ans++;
    }
  }
  
  cout << ans << endl;
}

// 0 0 1 1 0 1 0 1
// 0 0 1 9 0 1 0 1


