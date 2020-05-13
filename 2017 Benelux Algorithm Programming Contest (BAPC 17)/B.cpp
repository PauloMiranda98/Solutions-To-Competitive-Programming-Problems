#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
#define POINT_DOUBLE
#ifdef POINT_DOUBLE
  typedef double ftype;
  typedef long double ftLong;
  const long double EPS = 1e-9;
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
ftLong pw2(ftype a){
  return a *(ftLong)a;
}
ftLong dot(Point2d a, Point2d b){
  return pw2(a.x) + pw2(a.y);
}
ftLong norm(Point2d a){
  return dot(a, a);
}
double len(Point2d a){
  return sqrt(dot(a, a));
}
double dist(Point2d a, Point2d b){
  return len(a - b);
}
//End Point 2D

//Begin Line
struct Line{
  ftype a, b, c;
  Line() {}
  Line(ftype a, ftype b, ftype c) : a(a), b(b), c(c){
    normalize();
  }
  Line(Point2d p1, Point2d p2){
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
    normalize();
  }
  void normalize(){
#ifdef POINT_DOUBLE
    ftype z = sqrt(pw2(a) + pw2(b));
#else
    ftype z = __gcd(abs(a), __gcd(abs(b), abs(c)));
#endif
    a /= z;
    b /= z;
    c /= z;
    if (lt(a, 0) or (eq(a, 0) and lt(b, 0))){
      a = -a;
      b = -b;
      c = -c;
    }
  }
};
//End Line

//Begin Segment
struct Segment{
  Point2d a, b;
  Segment() {}
  Segment(Point2d a, Point2d b) : a(a), b(b) {}
};
inline bool betw(ftype l, ftype r, ftype x){
  return le(min(l, r), x) and le(x, max(l, r));
}
//End Segment

//Begin Circle 
struct Circle{
  ftype x, y, r;
  Circle() {}
  Circle(ftype x, ftype y, ftype r) : x(x), y(y), r(r){};
};
bool pointInCircle(Circle c, Point2d p){
  return ge(c.r, dist(Point2d(c.x, c.y), p));
}
//Return the number of the intersection
int circle_line_intersection(Circle circ, Line line, Point2d &p1, Point2d &p2){
  ftLong r = circ.r;
  ftLong a = line.a, b = line.b, c = line.c + line.a * circ.x + line.b * circ.y; //take a circle to the (0, 0)
  ftLong x0 = -a * c / (pw2(a) + pw2(b)), y0 = -b * c / (pw2(a) + pw2(b)); //(x0, y0) is the shortest distance point of the line for (0, 0)
  if (gt(pw2(c), pw2(r) * (pw2(a) + pw2(b)))){
    return 0;
  }else if(eq(pw2(c), pw2(r) * (pw2(a) + pw2(b)))){
    p1.x = p2.x = x0 + circ.x;
    p1.y = p2.y = y0 + circ.y;
    return 1;
  }else{
    ftLong d_2 =  pw2(r) -  pw2(c)/(pw2(a) + pw2(b));
    ftLong mult = sqrt(d_2 / (pw2(a) + pw2(b)));
    p1.x = x0 + b * mult + circ.x;
    p2.x = x0 - b * mult + circ.x;
    p1.y = y0 - a * mult + circ.y;
    p2.y = y0 + a * mult + circ.y;
    return 2;
  }
}
//Return the number of the intersection
int circle_intersection(Circle c1, Circle c2, Point2d &p1, Point2d &p2){
  if (eq(c1.x, c2.x) and eq(c1.y, c2.y)){
    if (eq(c1.r, c2.r))
      return -1; //INF
    else
      return 0;
  }else{
    Circle circ(0, 0, c1.r);
    Line line;
    line.a = -2*(c2.x - c1.x);
    line.b = -2*(c2.y - c1.y);
    line.c = pw2(c2.x - c1.x) + pw2(c2.y - c1.y) + pw2(c1.r) - pw2(c2.r);
    int sz = circle_line_intersection(circ, line, p1, p2);
    p1.x += c1.x;
    p2.x += c1.x;
    p1.y += c1.y;
    p2.y += c1.y;
    return sz;
  }
}
bool checkIfTheSegmentIsCompletelyCoveredByCircles(vector<Circle> &vc, Segment s){
  vector<Point2d> v = {s.a, s.b};
  Line l(s.a, s.b);
  for (Circle c : vc){
    Point2d p1, p2;
    int inter = circle_line_intersection(c, l, p1, p2);
    if (inter >= 1 and betw(s.a.x, s.b.x, p1.x) and betw(s.a.y, s.b.y, p1.y))
      v.push_back(p1);
    if (inter == 2 and betw(s.a.x, s.b.x, p2.x) and betw(s.a.y, s.b.y, p2.y))
      v.push_back(p2);
  }
  sort(v.begin(), v.end());
  bool ans = true;
  for (int i = 1; i < (int)v.size(); i++){
    bool has = false;
    for (Circle c : vc){
      if (pointInCircle(c, v[i - 1]) and pointInCircle(c, v[i])){
        has = true;
        break;
      }
    }
    ans = ans && has;
  }
  return ans;
}
//End Circle

vector<Point2d> vp;
int getID(Point2d p){
	return lower_bound(vp.begin(), vp.end(), p) - vp.begin();
}

template <typename T>
struct Dijkstra{
	typedef pair<T, int> pti;
	vector<vector<pti>> adj;
	vector<T> dist;
	vector<int> dad;
	int n;
	void init(int _n){
		n = _n;
		adj.assign(n, vector<pti>());
	}
	void addEdge(int from, int to, T w){
		adj[from].emplace_back(w, to);
	}
	void solve(int s){	
		dist.assign(n, numeric_limits<T>::max());
		dad.assign(n, -1);
		dist[s] = 0;
		priority_queue< pti, vector<pti>, greater<pti> > st;	
		st.push(pti(dist[s], s));	
		while(!st.empty()){
			T w = st.top().first;
			int u = st.top().second;
			st.pop();
			if(w > dist[u] + EPS) continue;
			for(pti p: adj[u]){
				T edge = p.first;  
				int to = p.second;
				if(w+edge+EPS < dist[to]){
					dist[to] = w + edge;
					dad[to] = u;
					st.push(pti(dist[to], to));
				}
			}
		}
	}	
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	Point2d a, b;
	cin >> a.x >> a.y;
	cin >> b.x >> b.y;
	int n;
	cin >> n;
	vector<Circle> vc(n);
	for(int i=0; i<n; i++)
		cin >> vc[i].x >> vc[i].y >> vc[i].r;
	vp = {a, b};
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			Point2d p1, p2;
			if(circle_intersection(vc[i], vc[j], p1, p2) >= 1){
				vp.push_back(p1);
				vp.push_back(p2);
			}
		}
	}
	sort(vp.begin(), vp.end());
	vp.erase(unique(vp.begin(), vp.end()), vp.end());

	Dijkstra<ftype> dijktra;
	dijktra.init(vp.size());
	for(int i=0; i<(int)vp.size(); i++){
		for(int j=i+1; j<(int)vp.size(); j++){
			if(checkIfTheSegmentIsCompletelyCoveredByCircles(vc, Segment(vp[i], vp[j]))){
				dijktra.addEdge(i, j, dist(vp[i], vp[j]));
				dijktra.addEdge(j, i, dist(vp[i], vp[j]));
			}
		}
	}
	int from = getID(a), to = getID(b);
	dijktra.solve(from);
	ftype ans = dijktra.dist[to];
	if(ans < 1e18)
		cout << fixed << setprecision(10) << ans << endl;
	else
		cout << "impossible" << endl;
	return 0;
}
