#include <bits/stdc++.h>
using namespace std;
//#define POINT_DOUBLE
#ifdef POINT_DOUBLE
  // Se necessario, apelar para __float128
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
  Point2d(ftype x1, ftype y1) : x(x1), y(y1) {}
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
  friend std::istream& operator >> (std::istream &is, Point2d &p) {
    return is >> p.x >> p.y;
  }
  friend std::ostream& operator << (std::ostream &os, const Point2d &p) {
    return os << p.x << ' ' << p.y;
  }
};
ftLong pw2(ftype a){
  return a * (ftLong)a;
}
//Scalar product
ftLong dot(Point2d a, Point2d b){
  return a.x*(ftLong)b.x + a.y*(ftLong)b.y;
}
ftLong norm(Point2d a){
  return dot(a, a);
}
double len(Point2d a){
  return sqrtl(dot(a, a));
}
double dist(Point2d a, Point2d b){
  return len(a - b);
}
//Vector product
ftLong cross(Point2d a, Point2d b){
  return a.x * (ftLong)b.y - a.y * (ftLong)b.x;
}
//Projection size from A to B
double proj(Point2d a, Point2d b){
  return dot(a, b) / len(b);
}
//The angle between A and B
double angle(Point2d a, Point2d b){
  return acos(dot(a, b) / len(a) / len(b));
}
//Left rotation. Angle in radian
Point2d rotateL(Point2d p, double ang){
  return Point2d(p.x * cos(ang) - p.y * sin(ang), p.x * sin(ang) + p.y * cos(ang));
}
//90 degree left rotation
Point2d perpL(Point2d a){
  return Point2d(-a.y, a.x);
}
//0-> 1o,2o quadrant, 1-> 3o,4o
int half(Point2d &p){
  if (gt(p.y, 0) or (eq(p.y, 0) and ge(p.x, 0)))
    return 0;
  else
    return 1;
}
//angle(a) < angle(b)
bool cmpByAngle(Point2d a, Point2d b){
  int ha = half(a), hb = half(b);
  if (ha != hb){
    return ha < hb;
  }else{
    ftLong c = cross(a, b);
    if(eq(c, 0))
      return lt(norm(a), norm(b));
    else
      return gt(c, 0);
  }
}
ftLong signed_area_parallelogram(Point2d p1, Point2d p2, Point2d p3){
    return cross(p2 - p1, p3 - p2);
}
long double triangle_area(Point2d p1, Point2d p2, Point2d p3){
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}
typedef long double ld;
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n;
  cin >> n;
  vector<Point2d> aux(n);
  for(int i=0; i<n; i++){
    cin >> aux[i];
  }
  aux.push_back(aux[0]);

  vector<Point2d> v(n);
  for(int i=0; i<n; i++)
    v[i] = aux[i+1] - aux[i];
  sort(v.begin(), v.end(), cmpByAngle);
  vector<Point2d> vp(n);
  vp[0] = {0, 0};
  for(int i=1; i<n; i++)
    vp[i] = vp[i-1] + v[i-1];
  for(int i=0; i<n; i++)
    vp.push_back(vp[i]);
  ld ans = 1e18;
  for(int i=0; i<n; i++){
    int lo = i+2, hi = i+n-1;
    Point2d base = vp[i+1] - vp[i];
    while(hi-lo >= 3){
      int mid1 = (lo*2 + hi)/3;
      int mid2 = (lo + hi*2)/3;
      Point2d d1 = vp[mid1]-vp[i], d2 = vp[mid2]-vp[i];

      if(abs(cross(d1, base)) <= abs(cross(d2, base)))
        lo = mid1;
      else
        hi = mid2;
    }
    ld mx = 0;
    for(int j=lo; j<=hi; j++) {
      Point2d d = vp[j] - vp[i];
      mx = max(mx, (ld)abs(cross(d, base)) / len(base));
    }
    ans = min(ans, mx);
  }
  cout << fixed << setprecision(2) << ans << endl;
  return 0;
}
