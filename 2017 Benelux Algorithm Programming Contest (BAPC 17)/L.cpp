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

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	
	map<string, long double> mp;
	mp["pink"] = 0;
	for(int i=0; i<n; i++){
		string a, b;
		long double r;
		cin >> a >> b >> r;
		if(mp.count(b)){
			if(mp.count(a))	
				mp[a] = max(mp[a], mp[b] + log10l(r));
			else
				mp[a] = mp[b] + log10l(r);
		}
	}
	if(mp.count("blue"))
		cout << fixed << setprecision(12) << powl(10, min((long double)1.0, mp["blue"])) << endl;
	else
		cout << fixed << setprecision(12) <<  0 << endl;
	return 0;
}
