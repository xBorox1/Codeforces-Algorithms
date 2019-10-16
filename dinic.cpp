#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 2e3 + 5;
const long long INF2 = 2e18, INF = 2e9 + 5;
const long long LOGQ = 30;

class Graph {
	public:

	int n, t, s;
	map<int, long long> cap[N];
	vector<int> NG[N];
	int odl[N];
	bool taken[N];
	long long flow;

	Graph(int n, int s, int t) {
		this->n = n;
		this->s = s;
		this->t = t;
		for(int i=0;i<=n;i++) cap[i].clear();
		flow = 0;
	}

	void add_edge(int x, int y, long long w) {
		cap[x][y] = w;
		cap[y][x] = 0;
	}

	long long dfs(int x, long long fl) {
		if(x == t) return fl;
		long long ans = 0;
		while(!NG[x].empty() && fl > 0) {
			int y = NG[x].back();
			long long re = 0;
			long long val = cap[x][y];
			if(val > 0) re = dfs(y, min(fl, val));
			if(re) {
				fl -= re;
				ans += re;
				cap[x][y] -= re;
				cap[y][x] += re;
			}
			NG[x].pop_back();
		}
		return ans;
	}

	bool Dinic(long long lim) {
		for(int i=0;i<=n;i++) {
			odl[i] = INF;
			NG[i].clear();
			taken[i] = 0;
		}

		odl[s] = 0;
		taken[s] = 1;
		vector<int> q = {s};

		for(int i=0;i<q.size();i++) {
			int x = q[i];
			for(auto y : cap[x]) if(y.second >= lim && odl[y.first] == INF) {
				odl[y.first] = odl[x] + 1;
				q.pb(y.first);
			}
		}

		if(odl[t] == INF) return 0;

		for(auto x : q)
		for(auto p : cap[x]) {
			int y = p.first;
			long long d = p.second;
			if(odl[y] == odl[x] + 1 && d >= lim && taken[x]) {
				NG[x].pb(y);
				taken[y] = 1;
			}
		}

		flow += dfs(s, INF2);
		return 1;
	}

	long long maxflow() {
		for(int i=LOGQ;i>=0;i--) while(Dinic((1<<i)));
		return flow;
	}
};

int main()
{
	int n, m, a;
	scanf("%d%d", &n, &m);

	Graph g(n + m + 1, 0, n + m + 1);

	for(int i=1;i<=n;i++) {
		scanf("%d", &a);
		g.add_edge(i + m, g.t, a); 
	}

	long long sum = 0;
	for(int i=1;i<=m;i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		sum += w;

		g.add_edge(g.s, i, w);
		g.add_edge(i, u + m, INF);
		g.add_edge(i, v + m, INF);
	}

	long long ans = sum - g.maxflow();
	printf("%lld", ans);
	return 0;
}
