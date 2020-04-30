#include <bits/stdc++.h>

#define X first
#define Y second
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
const int MAXN = 100010;

pii v[MAXN];
int ans[MAXN];
int fat[MAXN];
int invFat[MAXN];
int n;
map<pii, int> mp;
int fastExp(int base, int exp){
	int ans=1;
	while(exp > 0){
		if(exp & 1)
			ans = (ans*1LL*base)%MOD;
		base = (base*1LL*base)%MOD;
		exp >>= 1;
	}
	return ans;
}

int C(int i, int j){
	if(i < j)
		return 0;
	if(j < 0)
		return 0;
	return (((fat[i]*1LL*invFat[j])%MOD)*1LL*invFat[i-j])%MOD;
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;

	fat[0] = 1;
	for(int i=1; i<=n; i++)
		fat[i] = (fat[i-1]*1LL*i)%MOD;	
	invFat[n] = fastExp(fat[n], MOD-2); 	
	for(int i=n-1; i>=0; i--)
		invFat[i] = (invFat[i+1]*1LL*(i+1))%MOD;
	for(int i=0; i<n; i++){
		cin >> v[i].X >> v[i].Y;
		mp[pii(v[i].X*2, v[i].Y*2)]++;
	}
	for(int i=0; i<n; i++)
		for(int j=i+1; j<n; j++)
			mp[pii(v[i].X + v[j].X, v[i].Y + v[j].Y)] += 2;
	for(auto p: mp)
		ans[p.second]++;

	cout << n;
	for(int i=2; i<=n; i++){
		int res = 0;
		int inc = (i%2 == 0)? 1: 2;
		for(int j=i; j<=n; j+=inc)
			res = (res + (ans[j]*1LL*C(j/2, i/2))%MOD)%MOD;		
		cout << " " << res;
	}
	cout << endl;
	return 0;
}
