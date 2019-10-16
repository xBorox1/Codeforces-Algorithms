#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int D = (1<<19) + 5, pods = (1<<18) - 1;
int d[D];
void add(int x, int val) {
	x += pods;
	d[x] = val;
	while(x != 1) {
		x /= 2;
		d[x] = d[2*x] + d[2*x+1];
	}
}
int sum(int x, int y) {
	x += pods;
	y += pods;
	int ans = d[x];
	if(x != y) ans += d[y];
	while(x / 2 != y / 2) {
		if(x % 2 == 0) ans += d[x+1];
		if(y % 2 == 1) ans += d[y-1];
		x /= 2;
		y /= 2;
	}
	return ans;
}
int main()
{
	return 0;
}
