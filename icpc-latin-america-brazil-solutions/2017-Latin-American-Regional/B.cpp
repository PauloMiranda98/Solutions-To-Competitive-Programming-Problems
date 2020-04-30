#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3fLL
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1000000007;
int n;
bool isVowel(char c){
	return (c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u');		
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	string s;
	cin >> s;
	int vowel=0;
	int i=0, j=s.size()-1;
	for(char c: s){
		if(isVowel(c))
			vowel++;
	}
	if(vowel == 0){
		cout << 1 << endl;
		return 0;
	}
	bool left = true;
	while(i<=j){
		char a, b;
		if(left){
			a = s[i];
			b = s[j];
		}else{
			a = s[j];
			b = s[i];			
		}
		if(isVowel(a) and isVowel(b)){
			if(vowel == 1){
				cout << (j-i+1) << endl;
				return 0;
			}
			left = !left;
			vowel--;
		}else if(isVowel(a)){
			if(vowel == 1){
				cout << (j-i+1) << endl;
				return 0;
			}
		}else if(isVowel(b)){
			cout << 0 << endl;
			return 0;							
		}
		if(left)
			j--;
		else
			i++;
	}
	cout << 0 << endl;
	return 0;
}