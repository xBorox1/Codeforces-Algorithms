#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5;
int n, spoj[N];
vector<int> v[N];
bool inv[N], inv2[N];
stack<int> S;
void dfs(int x) {
	inv[x] = 1;
	for(auto y : v[x]) if(!inv[y]) dfs(y);
	S.push(x);
}
void dfs2(int x, int id) {
	inv2[x] = 1;
	spoj[x] = id;
	for(auto y : v[x]) if(!inv2[y]) dfs2(y, id);
}
void strongs() {
	for(int i=1;i<=n;i++) if(!inv[i]) dfs(i);
	int pnt = 1;
	while(!S.empty()) {
		int x = S.top();
		S.pop();
		if(!inv2[x]) dfs2(x, pnt);
		pnt++;
	}
}
int main()
{
	return 0;
}
