#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
const double EPS = 1e-9;

struct Line {
	mutable ll k, m;
	mutable double p;
	mutable int id;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(double x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<Line>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const double inf = 1/.0;
	double div(double a, double b) { // floored division
		return a / b;
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p + EPS >= y->p;
	}
	void add(ll k, ll m, int id) {
		auto z = insert({k, m, 0.0, id}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p+EPS >= y->p)
			isect(x, erase(y));
	}
};
const int MAXN = 100010;
const double inf = 1/.0;
double l[MAXN];
double r[MAXN];
int cont[MAXN];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<Line> v1, v2;
	LineContainer lc1, lc2;
	for(int i=1; i<=n; i++){
		int k1, b1, k2, b2;
		cin >> b1 >> k1 >> b2 >> k2;
		lc1.add(k1, b1, i);
		lc2.add(-k2, -b2, i);
	}
	vector<Line> hull(lc1.begin(), lc1.end());
	double last = -inf;
	for(Line line: hull){
		l[line.id] = max(0.0, last);
		r[line.id] = line.p;
		cont[line.id]++;
		last = line.p;
	}
		
	hull = vector<Line>(lc2.begin(), lc2.end());
	last = -inf;
	for(Line line: hull){
		l[line.id] = max(l[line.id], last);
		r[line.id] = min(r[line.id], line.p);
		cont[line.id]++;
		last = line.p;
	}

	int ans = 0;
	for(int i=1; i<=n; i++){
		if(cont[i] == 2 and r[i]-l[i] > EPS)
			ans++;
	}
	cout << ans << endl;
	
	return 0;
}
