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

string ans;

void brute(ll pos, ll totalPos, ll h, ll totalH, ll objetive){
  if(totalPos == 1){ 
    if(h == objetive)
      cout << "(*)";
       
    cout << ans << ": " << h << endl;
    return;
  }
  
  // Left  
  ans.push_back('L');
  if(pos < totalPos/2)
    brute(totalPos/2 - 1 - pos, totalPos/2, totalH - 1 - h, totalH*2, objetive);
  else
    brute(pos - totalPos/2, totalPos/2, totalH + h, totalH*2, objetive);
  ans.pop_back();

  // Right
  ans.push_back('R');
  if(pos < totalPos/2)
    brute(pos, totalPos/2, totalH + h, totalH*2, objetive);
  else
    brute(totalPos - 1 - pos, totalPos/2, totalH - 1 - h, totalH*2, objetive);
  ans.pop_back();  
}

stack<bool> opSum;

void solve1(ll h, ll totalH){
  if(totalH == 1)
    return;
  
  if(h & (totalH/2)){
    opSum.push(true);
    solve1(h - totalH/2, totalH/2);
  }else{
    opSum.push(false);
    solve1(totalH/2 - 1 - h, totalH/2);
  }
}

void solve2(ll pos, ll totalPos){
  if(totalPos == 1){        
    cout << ans << endl;
    return;
  }
  
  bool isSum = opSum.top();
  opSum.pop();
  
  if(pos < totalPos/2){
    if(isSum){
      ans.push_back('R');
      solve2(pos, totalPos/2);
    }else{
      ans.push_back('L');
      solve2(totalPos/2 - 1 - pos, totalPos/2);      
    }
  }else{
    if(isSum){
      ans.push_back('L');
      solve2(pos - totalPos/2, totalPos/2);
    }else{
      ans.push_back('R');
      solve2(totalPos - 1 - pos, totalPos/2);
    }    
  }  
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  
  ll a, b;
  cin >> a >> b;

  // brute(a-1, 1LL<<n, 0, 1LL, (1<<n) - b);

  solve1((1LL<<n) - b, 1LL<<n);
  solve2(a-1LL, 1LL<<n);
  
  return 0;
}
