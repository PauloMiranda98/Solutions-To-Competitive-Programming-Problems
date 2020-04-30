#include <iostream>
#include <queue>
#include <set>
#include <cmath>

using namespace std;

string texto;

int main(){
	long int cont = 0;
	 
	cin >> texto;
	
	for(char c : texto){
		cont += c - '0';
	}
	
	cout << cont%3 << endl;
		
	return 0;
}