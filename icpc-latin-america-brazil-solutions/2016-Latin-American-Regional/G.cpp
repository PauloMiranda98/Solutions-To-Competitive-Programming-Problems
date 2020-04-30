#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define all(x) x.begin(), x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m" << endl;

using namespace std;

std::mt19937 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 1000010;

int v[MAXN];
ll p_pow[MAXN];
string s;
int n, m;

int pos[30];
int nxt[MAXN];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int prime = 1000033;
	int mod = 1e9 + 9;
	p_pow[0] = 1;
	for (int i = 1; i < MAXN; i++)
		p_pow[i] = (p_pow[i - 1] * prime) % mod;

	cin >> s;
	n = s.size();
	cin >> m;

	ll pattern = 0;
	for (int i = 1; i <= 26; i++)
		pos[i] = -1;
	for (int i = 0; i < m; i++){
		int x, vx;
		cin >> x;
		if (pos[x] == -1 or i - pos[x] >= m)
			vx = 0;
		else
			vx = i - pos[x];

		pos[x] = i;
		pattern = (pattern + vx * p_pow[i]) % mod;
	}
	ll value_s = 0;
	for (int i = 1; i <= 26; i++)
		pos[i] = -1;
	for (int i = 0; i < m; i++){
		int x = s[i] - 'a' + 1, vx;
		if (pos[x] == -1 or i - pos[x] >= m)
			vx = 0;
		else
			vx = i - pos[x];
		if (pos[x] >= 0)
			nxt[pos[x]] = i;
		v[i] = vx;
		pos[x] = i;
		value_s = (value_s + vx * p_pow[i]) % mod;
	}
	int ans = (pattern == value_s);
	for (int j = m; j < n; j++){
		int x = s[j] - 'a' + 1, vx;
		if (pos[x] == -1 or j - pos[x] >= m)
			vx = 0;
		else
			vx = j - pos[x];

		if (pos[x] >= 0)
			nxt[pos[x]] = j;
		v[j] = vx;
		pos[x] = j;
		value_s = (value_s + vx * p_pow[j]) % mod;

		int i = j - m;
		value_s = ((value_s - v[i] * p_pow[i]) % mod + mod) % mod;
		if (i <= nxt[i] and nxt[i] <= j)
			value_s = ((value_s - v[nxt[i]] * p_pow[nxt[i]]) % mod + mod) % mod;

		v[nxt[i]] = 0;
		ans += ((pattern * p_pow[i + 1]) % mod == value_s);
	}
	cout << ans << endl;
	return 0;
}
