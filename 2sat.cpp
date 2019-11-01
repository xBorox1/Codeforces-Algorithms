#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5;
int n, m;
vector<int> v[2*N];

int norm(int x) {
	if(x < 0) return (-x - 1) * 2 + 1;
	return 2 * (x - 1);
}

void add_edge(int x, int y) {
	x = norm(x);
	y = norm(y);
	v[x].pb(y);
}

void add_alt(int x, int y) {
	add_edge(-x, y);
	add_edge(-y, x);
}

stack<int> S;
bool inv1[2*N], inv2[2*N];
int spoj[2*N], spojwsk;

void dfs1(int x) {
	inv1[x] = 1;
	for(auto y : v[x]) if(!inv1[y]) dfs1(y);
	S.push(x);
}

void dfs2(int x) {
	inv2[x] = 1;
	spoj[x] = spojwsk;
	for(auto y : v[x^1]) if(!inv2[y^1]) dfs2(y ^ 1);
}

bool sat() {
	for(int i=0;i<2*n;i++) if(!inv1[i]) dfs1(i);
	while(!S.empty()) {
		int x = S.top();
		S.pop();
		if(!inv2[x]) {
			spojwsk++;
			dfs2(x);
		}
	}

	for(int i=0;i<2*n;i++) if(spoj[i] == spoj[i^1]) return 0;
	return 1;
}

vector<int> spojne[2*N];
bool ozn[2*N];
bool rozw[N];

void roz() {
	for(int i=0;i<2*n;i++) spojne[spoj[i]].pb(i);
	for(int i=2*n;i>=1;i--) for(auto x : spojne[i]) {
		if(!ozn[x^1]) ozn[x] = 1;
	}

	for(int i=0;i<n;i++) if(ozn[2*i]) rozw[i] = 1;
}

int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		add_alt(a, b);
	}
	printf("%d\n", (int)sat());
	roz();
	for(int i=0;i<n;i++) cout<<rozw[i]<<" ";
	return 0;
}
