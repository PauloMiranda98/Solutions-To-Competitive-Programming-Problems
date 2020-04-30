#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3fLL
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1000000007;
int n;
string s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> s;
	n = s.size();

	vector<bool> d(n, false);
	for(int k=1; k<n; k++){
		if(n%k != 0)
			continue;
		for(int i=0; i<k; i++){
			if(s[i] != 'R')
				continue;
			int j = (i+k)%n;
			for(; j != i; j=(j+k)%n){
				if(s[j]!='R')
					break;				
			}
			if(j == i){
				d[k] = true;
				break;
			}
		}
	}
	int ans = 0;
	for(int k=1; k<n; k++){
		int g = __gcd(k, n);
		ans += d[g];
	}
	cout << ans << endl;
	return 0;
}