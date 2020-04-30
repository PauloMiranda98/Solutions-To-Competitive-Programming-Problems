#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double PI = acos(-1);
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());
	
	vector<int> ans;
	for(int i = 0; i < n; i+=2)
		ans.push_back(v[i]);
	for(int i = n-1-(n%2); i >= 0; i-=2)
		ans.push_back(v[i]);
	ll sum = 0;
	ans.push_back(ans[0]);
	for(int i = 0; i < n; i++)
		sum += ans[i]*ans[i+1];
	cout << fixed << setprecision(3) << sum*sinl(2*PI/(double)n)/2.0 << endl;
	
	return 0;
}