#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 200010;

int a[MAXN];
int b[MAXN];
ll sum[MAXN];

ll get_sum(int l, int r){
  if(l == 0)
    return sum[r];
  else
    return sum[r] - sum[l-1];
}

int l, k;
multiset<int> lt, gt;
ll sumSt = 0;

void fix(){
  while((int)gt.size() > l){
    auto it = gt.begin();
    int x = *it;
    
    sumSt -= x;
    gt.erase(gt.find(x));
    lt.insert(x);
  }

  while((int)gt.size() < l){
    auto it = lt.rbegin();
    int x = *it;
    
    sumSt += x;
    lt.erase(lt.find(x));
    gt.insert(x);
  }  
}

void add(int x){
  gt.insert(x);
  sumSt += x;
  
  fix();
}

void remove(int x){
  if(lt.find(x) != lt.end()){
    lt.erase(lt.find(x));
  }else{
    gt.erase(gt.find(x));
    sumSt -= x;
  }

  fix();
}


ll get_max(){
  return sumSt;
}

int main (){
  ios_base::sync_with_stdio(0);
  
  int n;
  cin >> n;
    
  for(int i=0; i<n; i++){
    cin >> a[i];
    a[n+i] = a[i];
  }

  for(int i=0; i<n; i++){
    cin >> b[i];
    b[n+i] = b[i];
  }
  
  sum[0] = a[0];
  for(int i=1; i<2*n; i++){
    sum[i] = sum[i-1] + a[i];
  }
  
  cin >> k >> l;
  
  ll ans = 0;
  for(int i=n-k; i<n; i++){
    lt.insert(b[i]);
  }
  fix();

  for(int i=n-k; i<=n; i++){
    ll suma = get_sum(i, i+k-1);
    ll mx = get_max();
    
    ans = max(ans, suma + mx);
    
    add(b[i + k]);
    remove(b[i]);
  }
  
  cout << ans << endl;
}

/*
5
9 7 2 2 9
5 2 2 3 1
2 1


5
9 7 2 2 9
5 9 2 3 1
2 1

*/


