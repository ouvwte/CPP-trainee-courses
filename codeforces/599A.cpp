#include <iostream>
using namespace std;
 
int main()
{
	int d1, d2, d3;
	cin >> d1 >> d2 >> d3;
	int res1, res2, res3, res4;
	res1 = d1 + d2 + d3;
	res2 = d1 * 2 + d2 * 2;
	res3 = d1 * 2 + d3 * 2;
	res4 = d2 * 2 + d3 * 2;
	if (res1 <= res2 && res1 <= res3 && res1 <= res4) {
		cout << res1;
	}
	else if (res2 <= res1 && res2 <= res3 && res2 <= res4) {
		cout << res2;
	}
	else if (res3 <= res1 && res3 <= res2 && res3 <= res4) {
		cout << res3;
	}
	else if (res4 <= res1 && res4 <= res2 && res4 <= res3) {
		cout << res4;
	}
	return 0;
}