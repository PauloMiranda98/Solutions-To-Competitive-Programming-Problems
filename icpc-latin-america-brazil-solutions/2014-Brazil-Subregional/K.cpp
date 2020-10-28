#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
const int MAXC = 200010;
int prefixSum[MAXC];

int sum(int i, int j){
  return prefixSum[j] - ((i>0)?prefixSum[i-1]:0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int c, n;
  cin >> c >> n;
  for(int i=0; i<n; i++){
    int x;
    cin >> x;
    prefixSum[x] = 1;
    prefixSum[c+x] = 1;
  }
  for(int i=1; i<2*c; i++)
    prefixSum[i] += prefixSum[i-1];

  int d = c/n;
  for(int i=0; i<d; i++){
    int ok = 0; 
    for(int j=1; j<=n; j++){
      ok += (sum(i+(j-1)*d, i+j*d - 1) == 1);
    }
    if(ok == n){
      cout << "S" << endl;
      return 0;
    }
  }
  
  cout << "N" << endl;
  return 0;
}
