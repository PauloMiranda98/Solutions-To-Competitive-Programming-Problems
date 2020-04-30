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
const int MAXN = 100010;
bool isPrime(int n){
	if(n < 2)
		return false;
	for(int i=2; i<=n/i; i++)
		if(n%i == 0)
			return false;
	return true;
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	for(int i=n; i>=2; i--){
		if(isPrime(i)){
			cout << i << endl;
			return 0;
		}
	}
	return 0;
}