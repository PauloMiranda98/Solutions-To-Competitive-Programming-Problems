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

int value[14];
int cnt[14];


void build(){
  for(int i=1; i<=13; i++){
    value[i] = min(i, 10);
    cnt[i] = 4;
  }
}

int readNext(){
  int x;
  cin >> x;
  cnt[x]--;

  return value[x];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int k;
  cin >> k;
  
  build();
  
  int play1 = readNext() + readNext();
  int play2 = readNext() + readNext();
  
  int sum = 0;
  for(int i=0; i<k; i++)
    sum += readNext();

  play1 += sum;
  play2 += sum;
  
  for(int i=1; i<=13; i++){
    if(cnt[i] == 0)
      continue;

    bool play1_lose = (play1 + value[i] > 23 and play2 + value[i] <= 23);
    bool play2_win = (play2 + value[i] == 23);

    if(play1_lose or play2_win){
      cout << i << endl;
      return 0;
    }
  }
  
  
  cout << -1 << endl;
  
  return 0;
}
