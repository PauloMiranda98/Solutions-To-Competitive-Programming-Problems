#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int D = 100;
const int MOD = 10000;

inline int modMul(int a, int b){
  return (a*b)%MOD;
}
inline int modSum(int a, int b){
  return (a+b)%MOD;
}
struct Matrix{
  int m[D][D];
  Matrix(bool identify = false){
    memset(m, 0, sizeof(m));
    for (int i = 0; i < D; i++)
      m[i][i] = identify;    
  }
  Matrix(vector<vector<int>> mat){
    for(int i=0; i<D; i++)
      for(int j=0; j<D; j++)
        m[i][j] = mat[i][j];    
  }
  int * operator[](int pos){
    return m[pos];
  }
  Matrix operator*(Matrix oth){
    Matrix ans;
    for (int i = 0; i < D; i++){
      for (int j = 0; j < D; j++){
        int &sum = ans[i][j];
        for (int k = 0; k < D; k++)
          sum = modSum(sum, modMul(m[i][k], oth[k][j]));
      }
    }
    return ans;
  }
};
Matrix fastPow(Matrix base, int exp){
  Matrix ans(true);
  while(exp){
    if(exp&1)
      ans = ans * base;
    base = base*base;
    exp>>=1;
  }
  return ans;
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, l, s, t;
  while(cin >> n >> l){
    cin >> s >> t; 
    s--; t--;

    Matrix base;
    for(int i=0; i<n; i++){
      for(int j=0; j<4; j++){
        int to;
        cin >> to;
        to--;
        base[i][to]++;
      }
    }
    base = fastPow(base, l);
    cout << base[s][t] << endl;
  }
  return 0;
}
