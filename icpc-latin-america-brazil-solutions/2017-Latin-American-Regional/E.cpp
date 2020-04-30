#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
int n, d;
bool see[1010][1010];
bool dp[1010][1010];
string s;
string aux;
string ans;
bool solve(int i, int sum){
	if(i == n){
		if(sum == 0){
			ans = aux;
			return true;
		}else{
			return false;
		} 
	}
	if(see[i][sum])
		return dp[i][sum];
	see[i][sum] = true;
	if(s[i] != '?'){
		aux.push_back(s[i]);
		bool ret = solve(i+1, ( (sum*10) + (s[i]-'0'))%d);
		aux.pop_back();
		return dp[i][sum] = ret;
	}
	for(int k=(i==0); k<10; k++){
		aux.push_back('0' + k);		
		bool ret = solve(i+1,( (sum*10) + k)%d);
		aux.pop_back();
		if(ret)			
			return dp[i][sum] = true;
	}
	return dp[i][sum] = false;
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> s >> d;
	n = s.size();
	solve(0, 0);
	if(ans.size() == 0)
		cout << "*" << endl;
	else
		cout << ans << endl;
	return 0;
}
