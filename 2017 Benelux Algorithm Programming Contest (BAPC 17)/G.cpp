#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using pii = pair<int, int>;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;

int dp[(1<<20) + 2];
int sum[(1<<20) + 2];
int v[22];
int n;

int solve(int mask){
	if(mask == 0)
		return 0;
	if(dp[mask] != -1)
		return dp[mask];
	int ans = 0;
	for(int i=0; i<n; i++){
		if(mask&(1<<i)){
			int new_mask = mask^(1<<i);
			ans = max(ans, solve(new_mask) + (sum[new_mask]==0));
		}
	}
	return dp[mask] = ans;
}
int main() {
	memset(dp, -1, sizeof(dp));
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int m;
	cin >> n >> m;
	
	for(int i=0; i<m; i++){
		int a, b, p;
		cin >> a >> b >> p;
		v[a] -= p;
		v[b] += p;
	}
	for(int mask=0; mask<(1<<n); mask++){
		int &s = sum[mask] = 0;
		for(int i=0; i<n; i++){
			if(mask&(1<<i))
				s += v[i];
		}
	}
	cout << n - solve((1<<n)-1) << endl;
	return 0;
}
