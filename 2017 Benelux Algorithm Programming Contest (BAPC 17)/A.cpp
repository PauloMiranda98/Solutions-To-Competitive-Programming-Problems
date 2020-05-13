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
	int m, n, x1, x2, y1, y2;
	double r;
	cin >> m >> n >> r;
	cin >> x1 >> y1;
	cin >> x2 >> y2;
	double ans = 1e18;
	for(int i=0; i<=n; i++){
		ans = min(ans, ((r/n)*(abs(y1-i)+abs(y2-i)) + (r/n)*i*(acos(-1)/m)*abs(x1-x2)));
	}
	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}
