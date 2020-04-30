#include <bits/stdc++.h>

using namespace std;

typedef double ftype;
const double EPS = 1e-9;

struct point2d {
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y): x(x), y(y) {}

};

vector<point2d> l[20], r[20];
double dx[20][20], mx[20], init[20];
double dp[1<<15][15];
int n;
double solve(int mask, int last){
	if(last == -1){
		double ans = 1e16;
		for(int i=0; i<n; i++)
			ans = min(ans, init[i] + solve(mask^(1<<i), i));		
		return ans;
	}
	if(mask == 0)
		return mx[last];
	if(dp[mask][last] > -EPS)
		return dp[mask][last];
	double ans = 1e16;
	for(int i=0; i<n; i++){
		if(mask&(1<<i))
			ans = min(ans, dx[last][i] + solve(mask^(1<<i), i));		
	}
	return dp[mask][last] = ans;	
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	for(int i=0; i<=14; i++)
		for(int j=0; j<=(1<<14); j++)
			dp[j][i] = -2;
	
	cin >> n;
	for(int i=0; i<n; i++){
		int k;
		cin >> k;
		vector<point2d> v(k);
		for(int j=0; j<k; j++){
			cin >> v[j].x >> v[j].y;
			mx[i] = max(mx[i], v[j].x);
			init[i] = max(init[i], -v[j].x);
		}
		v.push_back(v[0]);
		v.push_back(v[1]);
		int pos=0;
		while(abs(v[pos].y-v[pos+1].y) < EPS)
			pos++;
		while(abs(v[pos].y-v[pos+1].y) > EPS)
			r[i].push_back(v[pos++]);
		r[i].push_back(v[pos]);
		while(abs(v[pos].y-v[pos+1].y) < EPS)
			pos++;
		while(abs(v[pos].y-v[pos+1].y) > EPS)
			l[i].push_back(v[pos++]);
		l[i].push_back(v[pos]);
		reverse(l[i].begin(), l[i].end());
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			double ans = 0;
			for(auto p: l[j]){
				int lo = 0, hi=r[i].size()-1;
				int res1 = 0;
				while(lo <= hi){
					int mid = (lo+hi)/2;
					if(r[i][mid].y <= p.y){
						res1 = mid;
						lo = mid + 1;
					}else{
						hi = mid - 1;
					}
				}
				lo = 0, hi=r[i].size()-1;
				int res2 = hi;
				while(lo <= hi){
					int mid = (lo+hi)/2;
					if(r[i][mid].y >= p.y){
						res2 = mid;
						hi = mid - 1;
					}else{
						lo = mid + 1;
					}
				}
				auto p1 = r[i][res1];
				auto p2 = r[i][res2];
				
				if(p1.x == p2.x){
					ans = max(ans, p1.x-p.x);
				}else{
					double m = (p2.y-p1.y)/(p2.x-p1.x);
					double x = (p.y-p1.y)/m + p1.x;
					ans = max(ans, x-p.x);						
				}				
			}
			for(auto p: r[i]){
				int lo = 0, hi=l[j].size()-1;
				int res1 = 0;
				while(lo <= hi){
					int mid = (lo+hi)/2;
					if(l[j][mid].y <= p.y){
						res1 = mid;
						lo = mid + 1;
					}else{
						hi = mid - 1;
					}
				}
				lo = 0, hi=l[j].size()-1;
				int res2 = hi;
				while(lo <= hi){
					int mid = (lo+hi)/2;
					if(l[j][mid].y >= p.y){
						res2 = mid;
						hi = mid - 1;
					}else{
						lo = mid + 1;
					}
				}
				auto p1 = l[j][res1];
				auto p2 = l[j][res2];
				
				if(p1.x == p2.x){
					ans = max(ans, p.x-p1.x);
				}else{
					double m = (p2.y-p1.y)/(p2.x-p1.x);
					double x = (p.y-p1.y)/m + p1.x;
					ans = max(ans, p.x-x);						
				}				
			}			
			dx[i][j] = ans;
		}
	}
	cout << fixed << setprecision(3) << solve((1<<n)-1, -1) << endl;
	return 0;
}
