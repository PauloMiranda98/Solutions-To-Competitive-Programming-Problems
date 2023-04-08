#include <bits/stdc++.h>
#define F first
#define S second
#define endl '\n'
 
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};


//#define POINT_DOUBLE
#ifdef POINT_DOUBLE
  // Se necessario, apelar para __float128
  typedef double ftype;
  typedef long double ftLong;
  const double EPS = 1e-9;
  #define eq(a, b) (abs((a) - (b)) < EPS)
  #define lt(a, b) (((a) + EPS) < (b))
  #define gt(a, b) ((a) > ((b) + EPS))
  #define le(a, b) ((a) < ((b) + EPS))
  #define ge(a, b) (((a) + EPS) > (b))
#else
  typedef int32_t ftype;
  typedef int64_t ftLong;
  #define eq(a, b) ((a) == (b))
  #define lt(a, b) ((a) < (b))
  #define gt(a, b) ((a) > (b))
  #define le(a, b) ((a) <= (b))
  #define ge(a, b) ((a) >= (b))
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

//Vector product
ftLong cross(Point2d a, Point2d b){
  return a.x * (ftLong)b.y - a.y * (ftLong)b.x;
}

ftLong dot(Point2d a, Point2d b){
  return a.x*(ftLong)b.x + a.y*(ftLong)b.y;
}

ftLong norm(Point2d a){
  return dot(a, a);
}

inline bool betw(ftype l, ftype r, ftype x){
  return le(min(l, r), x) and le(x, max(l, r));
}

inline int sgn(ftLong x){
  return ge(x, 0) ? (eq(x, 0) ? 0 : 1) : -1;
}

//Checks if the point P belongs to the segment AB
bool pointInSegment(Point2d &a, Point2d &b, Point2d &p) {
  if(!eq(cross(a-p, b-p), 0))   
    return false;
  return betw(a.x, b.x, p.x) && betw(a.y, b.y, p.y);
}

bool pointInTriangle(Point2d a, Point2d b, Point2d c, Point2d p){
  ftLong s1 = abs(cross(b - a, c - a));
  ftLong s2 = abs(cross(a - p, b - p)) + abs(cross(b - p, c - p)) + abs(cross(c - p, a - p));
  return eq(s1, s2);
}

//If accept collinear points then change for <=
bool cw(Point2d a, Point2d b, Point2d c) {
  return lt(cross(b - a, c - b), 0);
}
//If accept collinear points then change for >=
bool ccw(Point2d a, Point2d b, Point2d c) {
  return gt(cross(b - a, c - b), 0);
}
// Returns the points clockwise
vector<Point2d> convex_hull(vector<Point2d> a){
  if (a.size() == 1)
    return a;
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  vector<Point2d> up, down;
  Point2d p1 = a[0], p2 = a.back();
  up.push_back(p1);
  down.push_back(p1);
  for (int i = 1; i < (int)a.size(); i++){
    if ((i == int(a.size() - 1)) || cw(p1, a[i], p2)){
      while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i]))
        up.pop_back();
      up.push_back(a[i]);
    }
    if ((i == int(a.size() - 1)) || ccw(p1, a[i], p2)){
      while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
        down.pop_back();
      down.push_back(a[i]);
    }
  }
  a.clear();
  for (int i = 0; i < (int)up.size(); i++)
    a.push_back(up[i]);  
  for (int i = down.size() - 2; i > 0; i--)
    a.push_back(down[i]);  
  return a;
}

struct ConvexPolygon{
  vector<Point2d> vp;  
  ConvexPolygon(vector<Point2d> v){  
    vp = convex_hull(v);
  }
  //O(log(N))
  //Accepts points on the edge
  bool pointInPolygon(Point2d point){ 
    if(vp.size() < 3)
      return pointInSegment(vp[0], vp[1], point);     
    if(!eq(cross(vp[1]-vp[0], point-vp[0]), 0) and sgn(cross(vp[1]-vp[0], point-vp[0])) != sgn(cross(vp[1]-vp[0], vp.back()-vp[0])) )
      return false;
    if(!eq(cross(vp.back()-vp[0], point-vp[0]), 0) and sgn(cross(vp.back()-vp[0], point-vp[0])) != sgn(cross(vp.back() - vp[0], vp[1]-vp[0])) )
      return false;
    if(eq(cross(vp[1]-vp[0], point-vp[0]), 0))
      return ge(norm(vp[1]-vp[0]), norm(point-vp[0]));
    int pos = 1, l = 1, r = vp.size() - 2;    
    while(l <= r){
      int mid = (l + r)/2;
      if(le(cross(vp[mid] - vp[0], point - vp[0]), 0)){
        pos = mid;
        l = mid+1;
      }else{ 
        r = mid-1;
      }
    }    
    return pointInTriangle(vp[0], vp[pos], vp[pos+1], point);
  } 
};

void reorderPolygon(vector<Point2d> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

// Returns the points clockwise
vector<Point2d> minkowski(vector<Point2d> P, vector<Point2d> Q, bool isClockwise){
    if(isClockwise){
      reverse(P.begin(), P.end());
      reverse(Q.begin(), Q.end());
    }
    reorderPolygon(P);
    reorderPolygon(Q);
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    vector<Point2d> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i] + Q[j]);
        auto c = cross(P[i + 1] - P[i], Q[j + 1] - Q[j]);
        if(c >= 0)
            ++i;
        if(c <= 0)
            ++j;
    }
    reverse(result.begin(), result.end());
    return result;
}

ConvexPolygon mulPolygon(ConvexPolygon p, ftype k){
  assert(k != 0);
  auto v = p.vp;
  for(auto &p: v)
    p = Point2d(k*p.x, k*p.y);
  return ConvexPolygon(v);
}

ConvexPolygon sumPolygon(ConvexPolygon p, ConvexPolygon q){
  return ConvexPolygon(minkowski(p.vp, q.vp, true));
}

ConvexPolygon subPolygon(ConvexPolygon p, ConvexPolygon q){
  return sumPolygon(p, mulPolygon(q, -1));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int m1;
  cin >> m1;
  
  vector<Point2d> v1(m1);
  for(int i=0; i<m1; i++)
    cin >> v1[i];
  ConvexPolygon p1(v1);
  
  int m2;
  cin >> m2;
  
  vector<Point2d> v2(m2);
  for(int i=0; i<m2; i++)
    cin >> v2[i];
  ConvexPolygon p2(v2);
  
  ConvexPolygon sum = sumPolygon(p1, p2);
  ConvexPolygon sub12 = subPolygon(mulPolygon(p1, 2), p2);
  ConvexPolygon sub21 = subPolygon(mulPolygon(p2, 2), p1);
  
  int n;
  cin >> n;
  
  for(int i=0; i<n; i++){
    Point2d p;
    cin >> p;
    
    if(sum.pointInPolygon(p*2) or sub12.pointInPolygon(p) or sub21.pointInPolygon(p))
      cout << 'Y';
    else
      cout << 'N';
  }
  
  cout << endl;

  return 0;
}
