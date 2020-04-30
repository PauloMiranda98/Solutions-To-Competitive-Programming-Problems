#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;

typedef ll ftype;

//Point2D
struct point2d{
	ftype x, y;
	point2d() {}
	point2d(ftype x, ftype y) : x(x), y(y) {}

	point2d &operator+=(const point2d &t){
		x += t.x;
		y += t.y;
		return *this;
	}
	point2d &operator-=(const point2d &t){
		x -= t.x;
		y -= t.y;
		return *this;
	}
	point2d &operator*=(ftype t){
		x *= t;
		y *= t;
		return *this;
	}
	point2d &operator/=(ftype t){
		x /= t;
		y /= t;
		return *this;
	}
	point2d operator+(const point2d &t) const{
		return point2d(*this) += t;
	}
	point2d operator-(const point2d &t) const{
		return point2d(*this) -= t;
	}
	point2d operator*(ftype t) const{
		return point2d(*this) *= t;
	}
	point2d operator/(ftype t) const{
		return point2d(*this) /= t;
	}
};

ftype cross(point2d a, point2d b){
	return a.x * b.y - a.y * b.x;
}

ll triangle_area(point2d p1, point2d p2, point2d p3){
	return abs(cross(p2 - p1, p3 - p2));
}

bool clockwise(point2d p1, point2d p2, point2d p3){
	return cross(p2 - p1, p3 - p2) <= 0;
}

bool counter_clockwise(point2d p1, point2d p2, point2d p3){
	return cross(p2 - p1, p3 - p2) >= 0;
}

bool valid(point2d p1, point2d p2, point2d p3, bool cw){
	if (cw)
		return cross(p2 - p1, p3 - p2) <= 0;
	else
		return cross(p2 - p1, p3 - p2) >= 0;
}

int n;
point2d v[100010];
point2d a, b;
ll memo[2][2][2][2][100010][2][2];

point2d n_v(int i, bool p){
	if (p)
		return v[i] + a;
	else
		return v[i] + b;
}

ll dp(bool cw, bool gz, bool f, bool s, int i, bool prev1, bool prev2){
	if (i == n){
		point2d p_f, p_s, p_prev1, p_prev2;
		p_prev1 = n_v(i - 2, prev1);
		p_prev2 = n_v(i - 1, prev2);
		p_f = n_v(0, f);
		p_s = n_v(1, s);

		if (valid(p_prev1, p_prev2, p_f, cw) and valid(p_prev2, p_f, p_s, cw)){
			return 0;
		}else{
			return INFLL;
		}
	}
	ll &ans = memo[cw][gz][f][s][i][prev1][prev2];
	if (ans != -1LL)
		return ans;
	ans = INFLL;
	point2d p_f, p_prev1, p_prev2, p_ia, p_ib;
	p_f = n_v(0, f);
	p_prev1 = n_v(i - 2, prev1);
	p_prev2 = n_v(i - 1, prev2);
	p_ia = n_v(i, true);
	p_ib = n_v(i, false);

	if (valid(p_prev1, p_prev2, p_ia, cw)){
		ll area = triangle_area(p_f, p_prev2, p_ia);
		ll v_dp = dp(cw, gz or area, f, s, i + 1, prev2, true);

		if (gz or area or v_dp)
			ans = min(ans, v_dp + area);
	}

	if (valid(p_prev1, p_prev2, p_ib, cw)){
		ll area = triangle_area(p_f, p_prev2, p_ib);
		ll v_dp = dp(cw, gz or area, f, s, i + 1, prev2, false);

		if (gz or area or v_dp)
			ans = min(ans, v_dp + area);
	}

	return ans;
}

int main(){
	memset(memo, -1, sizeof(memo));

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> v[i].x >> v[i].y;

	cin >> a.x >> a.y;
	cin >> b.x >> b.y;

	ll ans = INFLL;

	for (int cw = 0; cw < 2; cw++){
		for (int f = 0; f < 2; f++){
			for (int s = 0; s < 2; s++){
				ll x = dp(cw, 0, f, s, 2, f, s);

				if (x > 0)
					ans = min(ans, x);
			}
		}
	}

	printf("%01lld.%03lld\n", (ans * 125LL) / 1000LL, (ans * 125LL) % 1000LL);

	return 0;
}
