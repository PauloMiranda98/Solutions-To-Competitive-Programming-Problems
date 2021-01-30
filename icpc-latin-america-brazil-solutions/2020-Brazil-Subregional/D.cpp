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

inline int modSum(int a, int b, int mod = MOD){
  int ans = a+b;
  if(ans >= mod) ans -= mod;
  return ans;
}
inline int modSub(int a, int b, int mod = MOD){
  int ans = a-b;
  if(ans < 0) ans += mod;
  return ans;
}
inline int modMul(int a, int b, int mod = MOD){
  return (a*1LL*b)%mod;
}

const int D = 2;
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

vector<int> kmp(vector<int> &v) {
  int n = v.size();
  // pi[i] is the length of the longest proper prefix of the substring 
  // s[0..i] which is also a suffix of this substring.
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i-1];
    while (j > 0 and v[i] != v[j])
      j = pi[j-1];
    if (v[i] == v[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, m, k;
  cin >> n >> m >> k;
  vector<int> A(n), B(n);
  for(int i=0; i<n; i++){
    cin >> A[i];
  }
  for(int i=0; i<n; i++){
    cin >> B[i];
  }
  Matrix base({{0, n-1},
               {1, n-2}});
  auto res = fastPow(base, k);
  int f0_k = res[0][0], f1_k = res[1][0];
  
  vector<int> v;
  for(int i=1; i < n; i++){
    v.push_back(modSub(B[i-1]%m, B[i]%m, m));
  }
  v.push_back(-1);
  for(int i=1; i < 2*n - 1; i++){
    v.push_back(modSub(A[i%n]%m, A[(i-1)%n]%m, m));
  }
  auto pi = kmp(v);
  int ans = 0;
  for(int i=n; i<pi.size(); i++){
    int pos = (i - n - (n-1) + 1);
    if(pi[i] == n-1)
      ans = modSum(ans, (pos>0)?f1_k:f0_k);
  }
  cout << ans << endl;
  return 0;
}
