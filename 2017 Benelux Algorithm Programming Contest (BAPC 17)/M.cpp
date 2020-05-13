#include <bits/stdc++.h>

#define x first
#define y second
#define EB emplace_back
#define all(x) x.begin(), x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m" << endl;

using namespace std;

std::mt19937 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

vector<int> lis(vector<int> &v){
	vector<int> st, ans;
	vector<int> pos(v.size() + 1), dad(v.size() + 1);
	for (int i = 0; i < (int)v.size(); i++){
		//auto it = lower_bound(st.begin(), st.end(), v[i]); // Do not accept repeated values
		auto it = upper_bound(st.begin(), st.end(), v[i]); //Accept repeated values
		int p = it - st.begin();
		if (it == st.end())
			st.push_back(v[i]);
		else
			*it = v[i];
		pos[p] = i;
		dad[i] = (p == 0) ? -1 : pos[p - 1];
	}
	int p = pos[st.size() - 1];
	while (p >= 0){
		ans.push_back(v[p]);
		p = dad[p];
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int x0, y0, x1, y1;
	int n;
	cin >> n;
	cin >> x0 >> y0 >> x1 >> y1;
	vector<pii> v(n + 2);
	for (int i = 0; i < n; i++){
		cin >> v[i].x >> v[i].y;
	}
	v[n] = {x0, y0};
	v[n + 1] = {x1, y1};
	for (pii &p : v){
		if (x0 > x1)
			p.x = -p.x;
		if (y0 > y1)
			p.y = -p.y;
	}
	if (x0 > x1){
		x0 = -x0;
		x1 = -x1;
	}
	if (y0 > y1){
		y0 = -y0;
		y1 = -y1;
	}
	sort(all(v));
	vector<int> vp;
	for (auto p : v){
		if (x0 <= p.x and p.x <= x1 and y0 <= p.y and p.y <= y1)
			vp.push_back(p.y);
	}
	vector<int> ans = lis(vp);
	cout << ans.size() - 2 << endl;
	return 0;
}