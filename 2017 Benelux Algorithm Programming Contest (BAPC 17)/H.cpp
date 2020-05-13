#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

//#define POINT_DOUBLE
#ifdef POINT_DOUBLE
  typedef double ftype;
  typedef long double ftLong;
  const double EPS = 1e-9;
  #define eq(a, b) (abs(a - b) < EPS)
  #define lt(a, b) ((a + EPS) < b)
  #define gt(a, b) (a > (b + EPS))
  #define le(a, b) (a < (b + EPS))
  #define ge(a, b) ((a + EPS) > b)
#else
  typedef int32_t ftype;
  typedef int64_t ftLong;
  #define eq(a, b) (a == b)
  #define lt(a, b) (a < b)
  #define gt(a, b) (a > b)
  #define le(a, b) (a <= b)
  #define ge(a, b) (a >= b)
#endif

//Begin Point 2D
struct Point2d{
  ftype x, y;
  Point2d() {}
  Point2d(ftype x, ftype y) : x(x), y(y) {}
  Point2d operator+(const Point2d &t){
    return Point2d(x + t.x, y + t.y);
  }
  Point2d operator-(const Point2d &t){
    return Point2d(x - t.x, y - t.y);
  }
  Point2d operator*(ftype t){
    return Point2d(x * t, y * t);
  }
  Point2d operator/(ftype t){
    return Point2d(x / t, y / t);
  }
  bool operator<(const Point2d &o) const{
    return lt(x, o.x) or (eq(x, o.x) and lt(y, o.y));
  }
  bool operator==(const Point2d &o) const{
    return eq(x, o.x) and eq(y, o.y);
  }
};
ftLong cross(Point2d a, Point2d b){
  return a.x * (ftLong)b.y - a.y * (ftLong)b.x;
}
//End Point 2D

//Begin Segment
struct Segment{
  Point2d a, b;
  Segment() {}
  Segment(Point2d a, Point2d b) : a(a), b(b) {}
};
inline int sgn(ftLong x){
  return ge(x, 0) ? (eq(x, 0) ? 0 : 1) : -1;
}
bool inter1d(ftype a, ftype b, ftype c, ftype d){
  if (a > b)
    swap(a, b);
  if (c > d)
    swap(c, d);
  return le(max(a, c), min(b, d));
}
bool check_intersection(Segment s1, Segment s2){
  Point2d a = s1.a, b = s1.b, c = s2.a, d = s2.b;
  if (cross(a - c, d - c) == 0 && cross(b - c, d - c) == 0)
    return inter1d(a.x, b.x, c.x, d.x) && inter1d(a.y, b.y, c.y, d.y);
  return sgn(cross(b - a, c - a)) != sgn(cross(b - a, d - a)) &&
         sgn(cross(d - c, a - c)) != sgn(cross(d - c, b - c));
}
//End Segment
vector<bool> seen;
vector<vector<int>> adj;
void dfs(int u){
	seen[u] = true;
	for(int to: adj[u])
		if(!seen[to])
			dfs(to);
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	vector<Segment> vs(n);	
	for(int i=0; i<n; i++){
		Segment &s = vs[i];
		cin >> s.a.x >> s.a.y >> s.b.x >> s.b.y;
	}
	int comp = 0;
	int cnt = 0;
	adj.resize(n, vector<int>());
	seen.resize(n, false);
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(check_intersection(vs[i], vs[j])){
				cnt++;
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}
	for(int i=0; i<n; i++){
		if(!seen[i]){
			dfs(i);
			comp++;
		}			
	}
	
	//Euler Theorem
	//R = E - V + C
	//E = N + 2*intersect
	//V = 2*N + intersect
	//R = (N + 2*intersect) - (2*N + intersect) + C
	//R = intersect - N + C
	
	cout << (comp-n+cnt) << endl;
	return 0;
}