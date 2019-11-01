#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5, LOGN = 18;
int n, rod[N][LOGN], dep[N];
vector<int> v[N];

void dfs(int x) {
	dep[x] = dep[rod[x][0]] + 1;
	for(int i=1;i<LOGN;i++) rod[x][i] = rod[rod[x][i-1]][i-1];
	for(auto y : v[x]) if(rod[x][0] != y) {
		rod[y][0] = x;
		dfs(y);
	}
}

int jump(int x, int h) {
	for(int i=0;i<LOGN;i++, h /= 2)
		if(h % 2) x = rod[x][i];
	return x;
}

int LCA(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	y = jump(y, dep[y] - dep[x]);
	if(x == y) return x;
	for(int i=LOGN-1;i>=0;i--) if(rod[x][i] != rod[y][i]) {
		x = rod[x][i];
		y = rod[y][i];
	}
	return rod[x][0];
}

int main()
{
	scanf("%d", &n);
	for(int i=1;i<n;i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		v[a].pb(b);
		v[b].pb(a);
	}
	return 0;
}
