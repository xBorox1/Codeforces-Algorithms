#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5;

const int mod = 1e9 + 7;
void add_self(int &a, int b) {
	a += b;
	a %= mod;
}

void sub_self(int &a, int b) {
	a -= b;
	a %= mod;
	if(a < 0) a += mod;
}

long long mul(long long a, long long b) {
	return (__int128) a * b % mod;
}

long long my_pow(long long a, long long p) {
	if(p == 0) return 1;
	long long w = my_pow(a, p / 2);
	w = w * w % mod;
	if(p % 2) w = w * a % mod;
	return w;
}

long long my_inv(long long a) {
	return my_pow(a, mod - 2);
}

struct Massey {
  vector<int> start, coef; // 3 optional lines
  vector<vector<int>> powers;
  int memo_inv;
  int L;          
  Massey(vector<int> in) { // O(N^2)
    L = 0;
    int N = in.size();
    vector<int> C{1}, B{1};
    for (int n = 0; n < N; ++n) {
      assert(0 <= in[n] && in[n] < mod); // invalid input
      B.insert(B.begin(), 0);
      int d = 0;
      for (int i = 0; i <= L; ++i)
        add_self(d, mul(C[i], in[n - i]));
      if (d == 0)
        continue;
      vector<int> T = C;
      C.resize(max(B.size(), C.size()));
      for (int i = 0; i < (int)B.size(); ++i)
        sub_self(C[i], mul(d, B[i]));
      if (2 * L <= n) {
        L = n + 1 - L;
        B = T;
        d = my_inv(d);
        for (int &x : B)
          x = mul(x, d);
      }
    }
    for (int i = 1; i < (int)C.size(); ++i)
      coef.push_back((mod - C[i]) % mod);
    assert((int)coef.size() == L);
    for (int i = 0; i < L; ++i)
      start.push_back(in[i]);
    while (!coef.empty() && !coef.back()) {
      coef.pop_back();
      --L;
    }
    if (!coef.empty())
      memo_inv = my_inv(coef.back());
    powers.push_back(coef);
  }

  vector<int> mul_cut(vector<int> a, vector<int> b) {
    vector<int> r(2 * L - 1);
    for (int i = 0; i < L; ++i)
      for (int j = 0; j < L; ++j)
        add_self(r[i + j], mul(a[i], b[j]));
    while ((int)r.size() > L) {
      int value = mul(r.back(), memo_inv); // div(r.back(), coef.back());
      const int X = r.size();
      add_self(r[X - L - 1], value);
      for (int i = 0; i < L; ++i)
        sub_self(r[X - L + i], mul(value, coef[i]));
      assert(r.back() == 0);
      r.pop_back();
    }
    return r;
  }
  int get(long long k) { // O(L^2 * log(k))
    if (k < (int)start.size())
      return start[k];
    if (L == 0)
      return 0;
    k -= start.size();
    vector<int> vec = coef;
    for (int i = 0; (1LL << i) <= k; ++i) {
      if (i == (int)powers.size())
        powers.push_back(mul_cut(powers.back(), powers.back()));
      if (k & (1LL << i))
        vec = mul_cut(vec, powers[i]);
    }
    int total = 0;
    for (int i = 0; i < L; ++i)
      add_self(total, mul(vec[i], start[(int)start.size() - 1 - i]));
    return total;
  }

};

int main() {
	vector<int> in{0, 1, 0, 1, 0};
	Massey massey(in);
	for(int i=0;i<=20;i++) printf("%d ", massey.get(i));
	return 0;
}
