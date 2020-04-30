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
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int a1, b1, c1, a2, b2, c2;
	cin >> a1 >> b1 >> c1;
	cin >> a2 >> b2 >> c2;
	cout << max(0, a2-a1)+max(0, b2-b1)+max(0, c2-c1) << endl;
	return 0;
}