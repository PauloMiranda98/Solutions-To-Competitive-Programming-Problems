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
  int n, p;
  
  cin >> n >> p;
  p--;
  
  list<int> l;
  
  for(int i=0; i<n; i++){
    int x;
    cin >> x;
    
    l.push_back(x);
  }

  auto it = l.begin();
  while(p > 0){
    it++;
    p--;
  }
  
  int q;
  cin >> q;
  
  while(q--){
    string op;
    cin >> op;
    
    if(op == "print"){
      cout << *it << endl;
    }else if(op == "moveLeft"){
      if(it != l.begin())
        it--;
    }else if(op == "moveRight"){
      if(it != --l.end())
        it++;
    }else if(op == "insertLeft"){
      int x;
      cin >> x;
      
      l.insert(it, x);
    }else if(op == "insertRight"){
      int x;
      cin >> x;

      it++;
      l.insert(it, x);
      it--;
      it--;
    }else{
      assert(false);
    }
  }
  
  return 0;
}
