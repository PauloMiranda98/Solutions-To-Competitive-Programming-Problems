#include <iostream>

using namespace std;

int main(){
	int a, b, c;

	cin >> a >> b >> c;

	cout << min(2 * b + 4 * c, min(2 * a + 2 * c, 4 * a + 2 * b)) << endl;

	return 0;
}