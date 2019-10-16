#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 5e5 + 5, D = (1<<20) + 5, pods = (1<<19);
const long long INF = 2e9;
long long d[D], dod[D];
void upd(int x, int val) {
	dod[x] += val;
	if(x < pods) {
		d[x] = max(d[2*x], d[2*x+1]) + dod[x];
	}
	else d[x] = dod[x];
}
void _add(int v, int a, int b, int l, int r, long long val) {
	if(a > r || b < l) return;
	if(a == l && b == r) {
		upd(v, val);
		return;
	}
	int mid = (l + r) / 2;
	_add(2 * v, a, min(b, mid), l, mid, val);
	_add(2 * v + 1, max(a, mid + 1), b, mid + 1, r, val);
	d[v] = max(d[2*v], d[2*v+1]) + dod[v];
}
long long _maks(int v, int a, int b, int l, int r, long long val) {
	if(a > r || b < l) return 0;
	if(a == l && b == r) {
		return d[v] + val;
	}
	int mid = (l + r) / 2;
	long long ans = 0;
	ans = max(ans, _maks(2 * v, a, min(b, mid), l, mid, val + dod[v]));
	ans = max(ans, _maks(2 * v + 1, max(a, mid + 1), b, mid + 1, r, val + dod[v]));
	return ans;
}
long long maks(int x, int y) {
	return _maks(1, x, y, 1, pods, 0);
}
void add(int x, int y, int val) {
	_add(1, x, y, 1, pods, val);
}
int main()
{
	return 0;
}
