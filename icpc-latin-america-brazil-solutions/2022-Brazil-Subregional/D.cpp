#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main (){
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  int x, y;
  cin >> x >> y;
  int a=0, b=0;
 
  while(x%2 == 0){
    x /= 2;
    a++;  
  }
  
  while(y%2 == 0){
    y /= 2;
    b++;  
  }
  
  cout << max(n-a, n-b) - 1 << endl;
  
  return 0;
}


/*
7 7
1 2
2 3
3 1
6 1
6 4
4 5
7 6

7 7
2 1
3 2
1 3
1 6
4 6
5 4
6 7

*/


