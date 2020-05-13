#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;

int n;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	set<ll> ans;
	vector<ll> v_gcd;
	for(int i=0; i<n; i++){
		ll x;
		cin >> x;
		for(ll &g: v_gcd)
			g = (__gcd(x, g));
		v_gcd.push_back(x);
		sort(all(v_gcd));
		v_gcd.erase(unique(all(v_gcd)), v_gcd.end());
		for(ll &g: v_gcd)
			ans.insert(g);
	}
	cout << ans.size() << endl;
	return 0;
}
