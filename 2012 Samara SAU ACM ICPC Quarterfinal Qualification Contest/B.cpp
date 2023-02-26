#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define endl '\n'
 
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int dx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dy[] = {-1, 1,  0, 0, 1, -1, -1,  1};


// #define POINT_DOUBLE
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

ftLong area(Point2d a, Point2d b){
  return abs(cross(a, b));
}

ftLong area2(vector<Point2d> p){
  ftLong ret = 0;
  for (int i = 2; i < (int)p.size(); i++)
    ret += cross(p[i] - p[0], p[i - 1] - p[0]);
  return abs(ret);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n;
  cin >> n;
  
  vector<Point2d> v(n);
  for(int i=0; i<n; i++)
    cin >> v[i];

  for(int i=0; i<n; i++)
    v.push_back(v[i]);

  for(int i=0; i<n; i++)
    v.push_back(v[i]);
  
  ll total = area2(v);
  
  int j=2;
  
  ll curr = area(v[1] - v[0], v[2] - v[0]);
  ll mnDiff = abs((total - curr) - curr);
  
  pii ans(0, 2);
  
  for(int i=0; i<n; i++){
    while(curr*2 <= total){
      curr += area(v[j+1] - v[i], v[j] - v[i]);
      j++;
      
      ll other = (total - curr);
      ll diff = abs(other - curr);

      if(diff < mnDiff){
        ans = pii(i%n, j%n);
        mnDiff = diff;
      }
    }
    
    curr -= area(v[j] - v[i], v[i+1] - v[i]);
  }
  
  cout << ans.F + 1 << " " << ans.S +1 << endl;
  
  return 0;
}
