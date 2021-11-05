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
class UnionFind{
private:
  vector<int> p, w, sz;
public:
  UnionFind(int n){
    w.resize(n + 1, 1);
    sz.resize(n + 1, 1);
    p.resize(n + 1);
    for (int i = 0; i <= n; i++)
      p[i] = i;
  }
  int find(int x){
    if (p[x] == x)
      return x;
    return p[x] = find(p[x]);
  }
  bool join(int x, int y){
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    if (w[x] > w[y])
      swap(x, y);
    p[x] = y;
    sz[y] += sz[x];
    if (w[x] == w[y])
      w[y]++;
    return true;
  }
  bool isSame(int x, int y){
    return find(x) == find(y);
  }
  int size(int x){
    return sz[find(x)];
  }
};
const int MAXK = 20;

int getId(int i, int j){
  return i*MAXK + j;
}
pii recover(int x){
  return pii(x/MAXK, x%MAXK);
}
UnionFind uf(600010 * MAXK);

void isEqual(int a, int b, int x, int y){
  int sz = b-a+1;
  int k = 0;
  while( (1<<(k+1)) <= sz )
    k++;
  uf.join(getId(a, k), getId(x, k));
  uf.join(getId(b - (1<<k) + 1, k), getId(y - (1<<k) + 1, k));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m;
  cin >> n >> m;

  string s;
  cin >> s;

  string t = s;
  reverse(all(t));
  t = s + t;
  n = 2*n;
  for(int i=0; i<m; i++){
    int a, b;
    cin >> a >> b;
    a--; b--;

    int x = n - b - 1;
    int y = n - a - 1;

    isEqual(a, b, x, y);
  }
  for(int j=MAXK-1; j>0; j--){
    for(int i=0; i + (1<<j) <= n; i++){
      int a = getId(i, j);
      int b = uf.find(a);
      auto [k, l] = recover(b);

      uf.join(getId(i, j-1), getId(k, j-1));
      uf.join(getId(i + (1<<(j-1)), j-1), getId(k + (1<<(j-1)), j-1));
    }
  }
  for(int i=0; i<n; i++){
    uf.join(getId(i, 0), getId(n - 1 - i, 0));
  }

  set<int> st;
  map<int, bool> c0;
  map<int, bool> c1;

  for(int i=0; i<n; i++){
    int p = uf.find(getId(i, 0));
    st.insert(p);
    if(t[i] == '0')
      c0[p] = true;
    else if(t[i] == '1')
      c1[p] = true;
  }

  int ans = 1;
  for(int p: st){
    if(c0[p] and c1[p]){
      ans = 0;
    }else if(c0[p] or c1[p]){
      ans = ans;
    }else{
      ans = (ans + ans)%MOD;
    }
  }

  cout << ans << endl;
  return 0;
}
