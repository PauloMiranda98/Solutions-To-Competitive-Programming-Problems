#include <iostream>

using namespace std;
typedef long long int ll;

int main(){
	ll n;
	int cont = 0;
	
	cin >> n;
	
	for(ll i = 2LL; i*i <= n; i++){ 
		if(n%i == 0LL){
			cont++;
			
			while(n%i == 0LL)
				n /= i;
		}		
	}
	
	//Verificar se sobrou algum primo
	if(n > 1)
		cont++;
	
	ll res = 1LL<<cont;
	
	cout << res - (ll)cont - 1LL << endl;
	
	return 0;
}