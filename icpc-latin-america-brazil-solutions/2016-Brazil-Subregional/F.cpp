#include <bits/stdc++.h>

#define MAXN 90010

using namespace std;

struct No{
  int e;
  int c;
  int d;

  No(){
    e = c = d = 0;
  }

  No(int x, int y, int z){
    e = x;
    c = y;
    d = z;
  }
};

No treeA[10010];
No treeB[10010];
int mA = 0;
int mB = 0;

void maiorE(int x, int ac){
  if (x == 0){
    mA = max(mA, ac);
    return;
  }

  maiorE(treeA[x].e, 0);
  maiorE(treeA[x].c, ac + 1);
}

void maiorD(int x, int ac){
  if (x == 0){
    mB = max(mB, ac);
    return;
  }

  maiorD(treeB[x].c, ac + 1);
  maiorD(treeB[x].d, 0);
}

int n, m;
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;

  for (int i = 0; i < n; i++){
    int a, b, c;
    cin >> a >> b >> c;
    treeA[a] = No(b, c, 0);
  }

  cin >> m;

  for (int i = 0; i < m; i++){
    int a, b, c;
    cin >> a >> b >> c;
    treeB[a] = No(0, b, c);
  }

  maiorE(1, 0);
  maiorD(1, 0);

  int rA = 1;
  int rB = 1;

  No a = treeA[1];
  while (a.c){
    a = treeA[a.c];
    rA++;
  }

  No b = treeB[1];
  while (b.c){
    b = treeB[b.c];
    rB++;
  }

  cout << (n + m - max(min(mA, rB), min(mB, rA))) << endl;

  return 0;
}
