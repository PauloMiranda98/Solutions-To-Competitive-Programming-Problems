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

using namespace std;

inline int getId(char c){
  if(c == '$')
    return 26;
  return c - 'a';
}

struct SuffixAutomaton{
  struct state{
    int len, link, first_pos;
    bool is_clone = false;
    array<int, 27> next;
    state(){
      for(int i=0; i<27; i++){
        next[i] = -1;
      }
    }
  };
  vector<state> st;
  int sz, last;
  SuffixAutomaton(string s){
    st.resize(2 * s.size() + 10);
    st[0].len = 0;
    st[0].link = -1;
    st[0].is_clone = false;
    sz = 1;
    last = 0;
    for (char c : s)
      insert(c);
  }
  void insert(char c0){
    int c = getId(c0);
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = st[cur].len - 1;
    st[cur].is_clone = false;
    int p = last;
    while (p != -1 && st[p].next[c] == -1){
      st[p].next[c] = cur;
      p = st[p].link;
    }
    if (p == -1){
      st[cur].link = 0;
    }else{
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len){
        st[cur].link = q;
      }else{
        int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        st[clone].first_pos = st[q].first_pos;
        st[clone].is_clone = true;
        while (p != -1 && st[p].next[c] == q){
          st[p].next[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }
  void nxt(int &v, int &l, char c0){
    int c = getId(c0);
    while (v and st[v].next[c] == -1){
      v = st[v].link;
      l = st[v].len;
    }
    if (st[v].next[c] != -1){
      v = st[v].next[c];
      l++;
    }
  }
};

using namespace std;
class SegTreeIterative{
private:
  typedef int Node;
  Node neutral = 0;
  vector<Node> st;
  int n;
  inline Node join(Node a, Node b){
    return max(a, b);
  }
public:
  template <class MyIterator>
  SegTreeIterative(MyIterator begin, MyIterator end){
    int sz = end - begin;
    for (n = 1; n < sz; n <<= 1);
    st.assign(n << 1, neutral);
    for (int i = 0; i < sz; i++, begin++)
      st[i + n] = (*begin);
    for (int i = n - 1; i; i--){
      st[i] = join(st[(i << 1)], st[(i << 1) + 1]);
    }
  }
  //0-indexed
  void update(int i, Node x){
    st[i += n] = x;
    for (i >>= 1; i; i >>= 1)
      st[i] = join(st[i << 1], st[(i << 1) + 1]);
  }
  //0-indexed [l, r]
  Node query(int l, int r){
    Node ansL = neutral, ansR = neutral;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1){
      if (l & 1)
        ansL = join(ansL, st[l++]);
      if (r & 1)
        ansR = join(st[--r], ansR);
    }
    return join(ansL, ansR);
  }
  Node lower_bound(int k){
    int no=1, l=0, r=n-1;
    while(l<r){
      int mid = (l+r)>>1;
      int lo = no<<1;
      if(st[lo] >= k){
        no = lo;
        r = mid;
      }else{
        k -= st[lo];
        no = lo + 1;
        l = mid + 1;
      }
    }
    if(st[no] >= k)
      return l;
    else
      return -1;
  }
};

const int MAXL = 300010;

vector<int> in[MAXL];
vector<int> out[MAXL];
int mx0[MAXL], mx1[MAXL];
int mx2[MAXL], feq[MAXL];

void add(int i, int j, int x){
  in[i].push_back(x);
  out[j+1].push_back(x);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  string T;
  for(int i=0; i<m; i++){
    string t;
    cin >> t;
    for(char c: t)
      T += c;
    T += '$';
  }

  SuffixAutomaton sa(T);
  int no = 0, sz = 0;

  for(int i=0; i<n; i++){
    sa.nxt(no, sz, s[i]);
  }

  for(int i=0; i<n; i++){
    sa.nxt(no, sz, s[i]);
    if(sz == 0)
      continue;

    mx0[i] = max(mx0[i], sz);

    int delta = max(0, n - sz);
    int j = min(3*n, i + delta);
    mx1[j] = max(mx1[j], sz);

    add(i, j, min(n, sz));
  }

  for(int i=1; i<3*n; i++){
    mx1[i] = max(mx1[i], mx1[i-1] - 1);
  }
  for(int i=3*n-2; i>=0; i--){
    mx0[i] = max(mx0[i], mx0[i+1] - 1);
  }
  vector<int> aux(n+1, 0);
  SegTreeIterative st(all(aux));

  int last = -1;
  int curr = 0;
  int res = 0;

  for(int i=0; i<3*n; i++){
    for(int x: out[i]){
      feq[x]--;
      if(feq[x] == 0){
        st.update(x, 0);
      }
      curr++;
    }
    for(int x: in[i]){
      feq[x]++;
      st.update(x, x);
      curr++;
    }
    if(curr == last){
      mx2[i] = max(mx2[i], res);
    }else{
      last = curr;
      res = st.query(0, n-1);
      mx2[i] = max(mx2[i], res);
    }
    mx2[i] = max(mx2[i], mx0[i]);
    mx2[i] = max(mx2[i], mx1[i]);
  }
  int mn = n;
  for(int i=0; i<n; i++){
    int x = max({mx2[i], mx2[n + i], mx2[2*n + i]});
    mn = min(mn, x);
  }
  cout << mn << endl;
  return 0;
}
