#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) x.begin(),x.end()
//#define endl '\n'
 
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000000;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};

//Source: https://github.com/zimpha/algorithmic-library/blob/master/cpp/mathematics/linear-recurrence.cc
struct LinearRecurrence {
  using int64 = long long;
  using vec = std::vector<int64>;
  static void extend(vec &a, size_t d, int64 value = 0) {
    if (d <= a.size()) return;
    a.resize(d, value);
  }
  static vec BerlekampMassey(const vec &s, int64 mod) {
    std::function<int64(int64)> inverse = [&](int64 a) {
      return a == 1 ? 1 : (int64)(mod - mod / a) * inverse(mod % a) % mod;
    };
    vec A = {1}, B = {1};
    int64 b = s[0];
    assert(b != 0);
    for (size_t i = 1, m = 1; i < s.size(); ++i, m++) {
      int64 d = 0;
      for (size_t j = 0; j < A.size(); ++j) {
        d += A[j] * s[i - j] % mod;
      }
      if (!(d %= mod)) continue;
      if (2 * (A.size() - 1) <= i) {
        auto temp = A;
        extend(A, B.size() + m);
        int64 coef = d * inverse(b) % mod;
        for (size_t j = 0; j < B.size(); ++j) {
          A[j + m] -= coef * B[j] % mod;
          if (A[j + m] < 0) A[j + m] += mod;
        }
        B = temp, b = d, m = 0;
      } else {
        extend(A, B.size() + m);
        int64 coef = d * inverse(b) % mod;
        for (size_t j = 0; j < B.size(); ++j) {
          A[j + m] -= coef * B[j] % mod;
          if (A[j + m] < 0) A[j + m] += mod;
        }
      }
    }
    return A;
  }
  static void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
    if (!b) x = 1, y = 0, g = a;
    else {
      exgcd(b, a % b, g, y, x);
      y -= x * (a / b);
    }
  }
  static int64 crt(const vec &c, const vec &m) {
    int n = c.size();
    int64 M = 1, ans = 0;
    for (int i = 0; i < n; ++i) M *= m[i];
    for (int i = 0; i < n; ++i) {
      int64 x, y, g, tm = M / m[i];
      exgcd(tm, m[i], g, x, y);
      ans = (ans + tm * x * c[i] % M) % M;
    }
    return (ans + M) % M;
  }
  static vec ReedsSloane(const vec &s, int64 mod) {
    auto inverse = [] (int64 a, int64 m) {
      int64 d, x, y;
      exgcd(a, m, d, x, y);
      return d == 1 ? (x % m + m) % m : -1;
    };
    auto L = [] (const vec &a, const vec &b) {
      int da = (a.size() > 1 || (a.size() == 1 && a[0])) ? a.size() - 1 : -1000;
      int db = (b.size() > 1 || (b.size() == 1 && b[0])) ? b.size() - 1 : -1000;
      return std::max(da, db + 1);
    };
    auto prime_power = [&] (const vec &s, int64 mod, int64 p, int64 e) {
      // linear feedback shift register mod p^e, p is prime
      std::vector<vec> a(e), b(e), an(e), bn(e), ao(e), bo(e);
      vec t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1, 1);;
      for (int i = 1; i <= e; ++i) {
        pw[i] = pw[i - 1] * p;
        assert(pw[i] <= mod);
      }
      for (int64 i = 0; i < e; ++i) {
        a[i] = {pw[i]}, an[i] = {pw[i]};
        b[i] = {0}, bn[i] = {s[0] * pw[i] % mod};
        t[i] = s[0] * pw[i] % mod;
        if (t[i] == 0) {
          t[i] = 1, u[i] = e;
        } else {
          for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
        }
      }
      for (size_t k = 1; k < s.size(); ++k) {
        for (int g = 0; g < e; ++g) {
          if (L(an[g], bn[g]) > L(a[g], b[g])) {
            ao[g] = a[e - 1 - u[g]];
            bo[g] = b[e - 1 - u[g]];
            to[g] = t[e - 1 - u[g]];
            uo[g] = u[e - 1 - u[g]];
            r[g] = k - 1;
          }
        }
        a = an, b = bn;
        for (int o = 0; o < e; ++o) {
          int64 d = 0;
          for (size_t i = 0; i < a[o].size() && i <= k; ++i) {
            d = (d + a[o][i] * s[k - i]) % mod;
          }
          if (d == 0) {
            t[o] = 1, u[o] = e;
          } else {
            for (u[o] = 0, t[o] = d; t[o] % p == 0; t[o] /= p, ++u[o]);
            int g = e - 1 - u[o];
            if (L(a[g], b[g]) == 0) {
              extend(bn[o], k + 1);
              bn[o][k] = (bn[o][k] + d) % mod;
            } else {
              int64 coef = t[o] * inverse(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
              int m = k - r[g];
              assert(m >= 0);
              extend(an[o], ao[g].size() + m);
              extend(bn[o], bo[g].size() + m);
              for (size_t i = 0; i < ao[g].size(); ++i) {
                an[o][i + m] -= coef * ao[g][i] % mod;
                if (an[o][i + m] < 0) an[o][i + m] += mod;
              }
              while (an[o].size() && an[o].back() == 0) an[o].pop_back();
              for (size_t i = 0; i < bo[g].size(); ++i) {
                bn[o][i + m] -= coef * bo[g][i] % mod;
                if (bn[o][i + m] < 0) bn[o][i + m] -= mod;
              }
              while (bn[o].size() && bn[o].back() == 0) bn[o].pop_back();
            }
          }
        }
      }
      return std::make_pair(an[0], bn[0]);
    };

    std::vector<std::tuple<int64, int64, int>> fac;
    for (int64 i = 2; i * i <= mod; ++i) if (mod % i == 0) {
      int64 cnt = 0, pw = 1;
      while (mod % i == 0) mod /= i, ++cnt, pw *= i;
      fac.emplace_back(pw, i, cnt);
    }
    if (mod > 1) fac.emplace_back(mod, mod, 1);
    std::vector<vec> as;
    size_t n = 0;
    for (auto &&x: fac) {
      int64 mod, p, e;
      vec a, b;
      std::tie(mod, p, e) = x;
      auto ss = s;
      for (auto &&x: ss) x %= mod;
      std::tie(a, b) = prime_power(ss, mod, p, e);
      as.emplace_back(a);
      n = std::max(n, a.size());
    }
    vec a(n), c(as.size()), m(as.size());
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < as.size(); ++j) {
        m[j] = std::get<0>(fac[j]);
        c[j] = i < as[j].size() ? as[j][i] : 0;
      }
      a[i] = crt(c, m);
    }
    return a;
  }

  LinearRecurrence(const vec &s, const vec &c, int64 mod):
    init(s), trans(c), mod(mod), m(s.size()) {}
  LinearRecurrence(const vec &s, int64 mod, bool is_prime = true): mod(mod) {
    assert(s.size() % 2 == 0);
    vec A;
    if (is_prime) A = BerlekampMassey(s, mod);
    else A = ReedsSloane(s, mod);
    m = s.size() / 2;
    A.resize(m + 1, 0);
    trans.resize(m);
    for (int i = 0; i < m; ++i) {
      trans[i] = (mod - A[i + 1]) % mod;
    }
    if (m == 0) m = 1, trans = {1};
    std::reverse(trans.begin(), trans.end());
    init = {s.begin(), s.begin() + m};
  }
  int64 calc(int64 n) {
    if (MOD == 1) return 0;
    if (n < m) return init[n];
    vec v(m), u(m << 1);
    int64 msk = !!n;
    for (int64 m = n; m > 1; m >>= 1) msk <<= 1;
    v[0] = 1 % MOD;
    for (int64 x = 0; msk; msk >>= 1, x <<= 1) {
      std::fill_n(u.begin(), m * 2, 0);
      x |= !!(n & msk);
      if (x < m) u[x] = 1 % MOD;
      else {// can be optimized by fft/ntt
        for (int i = 0; i < m; ++i) {
          for (int j = 0, t = i + (x & 1); j < m; ++j, ++t) {
            u[t] = (u[t] + v[i] * v[j]) % MOD;
          }
        }
        for (int i = m * 2 - 1; i >= m; --i) {
          for (int j = 0, t = i - m; j < m; ++j, ++t) {
            u[t] = (u[t] + trans[j] * u[i]) % MOD;
          }
        }
      }
      v = {u.begin(), u.begin() + m};
    }
    int64 ret = 0;
    for (int i = 0; i < m; ++i) {
      ret = (ret + v[i] * init[i]) % MOD;
    }
    return ret;
  }
  vec init, trans;
  int64 mod;
  int m;
};

ll f[11][402];

ll dp[8022][402];


void build(){
  for(int k=0; k<=400; k++)
    dp[0][k] = 1;
  
  for(int i=1; i<=8020; i++){
    for(int k=0; k<=400; k++){
      ll ans = 0;
      for(int d=1; d<=min(i, 10); d++){
        for(int p=0; p<=k; p++){
          ans += (dp[i - d][k - p]*f[d][p]);
        }
        ans %= MOD;
      }

      dp[i][k] = ans%MOD;
    }
  }
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
  
  vector<ll> v;
  build();
  
  for(int i=0; i<2*10*(k+1); i++){
    v.push_back(dp[i][k]);
  }
  
  LinearRecurrence lr(v, (ll)MOD, false);
  
  cout << lr.calc(n-1) << endl;
  
  return 0;
}

/*
1000000000 3 400
1 9
2 0
7 3
*/
