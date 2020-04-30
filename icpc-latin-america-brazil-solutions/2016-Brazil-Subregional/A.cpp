#include <iostream>

using namespace std;

int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	int a, b, c;
	cin >> a >> b >> c;

	if ((a == b) or (a == c) or (b == c) or ((a + b) == c) or ((a + c) == b) or ((b + c) == a))
		cout << "S" << "\n";
	else
		cout << "N" << "\n";

	return 0;
}
