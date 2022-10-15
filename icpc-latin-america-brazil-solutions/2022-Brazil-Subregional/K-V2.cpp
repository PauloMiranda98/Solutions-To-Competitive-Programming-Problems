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
const int MOD = 1000000000;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};

const int MAXK = 400;

struct Poly{
  ll x[MAXK + 1];
  Poly(){
    memset(x, 0, sizeof(x));
  }
};

Poly mulPoly(Poly &a, Poly &b){
  Poly ans;
  
  for(int i=0; i<=MAXK; i++){
    for(int j=0; i+j<=MAXK; j++){
      ans.x[i+j] = (ans.x[i+j] + (a.x[i] * b.x[j]))%MOD;
    }
  }
  
  return ans;
}

Poly sumPoly(Poly &a, Poly &b){
  Poly ans;
  
  for(int i=0; i<=MAXK; i++){
    ans.x[i] = (a.x[i] + b.x[i])%MOD;
  }
  
  return ans;
}

const int D = 10;
struct Matrix{
  Poly m[D][D];
  Matrix(bool identify = false){
    Poly empty;
    Poly neutral;
    neutral.x[0] = 1;

    for(int i=0; i<D; i++)
      for(int j=0; j<D; j++)
        m[i][j] = empty;

    if(identify){
      for (int i = 0; i < D; i++)
        m[i][i] = neutral;
    }
  }
  Poly * operator[](int pos){
    return m[pos];
  }
  Matrix operator*(Matrix oth){
    Matrix ans;
    for (int i = 0; i < D; i++){
      for (int j = 0; j < D; j++){
        for (int k = 0; k < D; k++){
          auto aux = mulPoly(m[i][k], oth[k][j]);
          ans[i][j] = sumPoly(ans[i][j], aux);
        }
      }
    }
    return ans;
  }
};

Matrix fastPow(Matrix base, ll exp){
  Matrix ans(true);
  while(exp){
    if(exp&1LL)
      ans = ans * base;
    base = base*base;
    exp>>=1;
  }
  return ans;
}

int f[D + 1][MAXK + 1];



int solve(int n, int k){
  Matrix base;
  
  // x1 = 1 * x^0 
  Poly x1;
  x1.x[0] = 1;

  // Init base matrix
  for(int i=0; i<D; i++){
    for(int j=0; j<=MAXK; j++)
      base[0][i].x[j] = f[i+1][j];
  }
  
  for(int i=1; i<D; i++)
    base[i][i-1] = x1;
  
  // Compute answer
  auto result = fastPow(base, n);

  int ans = 0;
  for(int i=0; i<=k; i++){
    ans = (ans + result[0][0].x[i])%MOD;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  
  int n, m, k;
  cin >> n >> m >> k;
  
  for(int i=0; i<m; i++){
    int d, p;
    cin >> d >> p;

    f[d][p]++;
  }
  
  cout << solve(n-1, k) << endl;
  
  return 0;
}

/*
1000000000 3 400
1 9
2 0
7 3
--------
3 3 10
1 3
2 0
3 1
*/
