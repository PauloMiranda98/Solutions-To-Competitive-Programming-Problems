#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

typedef pair<int, int> pii;

namespace SCC{
  vector<vector<int>> adj, revAjd;
  vector<bool> visited;
  vector<int> ts, component;
  
  void dfs1(int u){
  visited[u] = true;
    for(int to: adj[u]){
      if(!visited[to])
        dfs1(to);
    }
    ts.push_back(u);
  }
  
  void dfs2(int u, int c){
    component[u] = c;
    for(int to: revAjd[u]){
      if(component[to] == -1)
        dfs2(to, c);  
    }
  }
  
  pair<int, vector<int>> scc(int n, vector<pii> &edges){
    adj.assign(n, vector<int>());
    revAjd.assign(n, vector<int>());
    visited.assign(n, false);
    component.assign(n, -1);
    for(auto [a, b]: edges){
      adj[a].push_back(b);
      revAjd[b].push_back(a); 
    }
    
    ts.clear();
    for(int i=0; i<n; i++){
      if(!visited[i])
        dfs1(i);  
    }
    reverse(ts.begin(), ts.end());
    int comp = 0;
    for(int u: ts){
      if(component[u] == -1)
        dfs2(u, comp++);
    }
    return {comp, component};
  }
};

int main (){
  ios_base::sync_with_stdio(0);
  
  int n, m;
  cin >> n >> m;
  
  vector<pii> edges;
  for(int i=0; i<m; i++){
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    edges.emplace_back(a, b);  
  }

  auto [k, comp] = SCC::scc(n, edges);

  vector<int> in(k, 0), out(k, 0);
  for(auto [a, b]: edges){
    if(comp[a] == comp[b])
      continue;
  
    in[comp[b]]++;
    out[comp[a]]++;  
  }
  if(k == 1){
    cout << 0 << endl;  
  }else{
    int a=0, b=0;

    for(int i=0; i<k; i++){
      if(in[i] == 0){
        a++;  
      }
      
      if(out[i] == 0){
        b++;
      }
    }

    cout << max(a, b) << endl;
  }
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


