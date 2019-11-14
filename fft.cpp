#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const long double PI = 2LL * acos(-1);

struct cmx {
	long double x, y;
};
cmx operator +(cmx &a, cmx &b) { return {a.x + b.x, a.y + b.y}; }
cmx operator -(cmx &a, cmx &b) { return {a.x - b.x, a.y - b.y}; }
cmx operator *(cmx &a, cmx &b) { return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }
cmx ll(long long x) {return {(long double)x, 0LL}; }

typedef vector<long long> VI;
typedef vector<cmx> CI;

int bit_reverse(int x, int logn) {
	int n = 0;
	for(int i=0;i<logn;i++) {
		n <<= 1;
		n |= (x & 1);
		x >>= 1;
	}
	return n;
}

CI FFT(CI &A, bool num) {
	int n = A.size();

	int logn = 0;
	int nn = n;
	while(nn) {
		nn /= 2;
		logn++;
	}	
	logn--;

	CI B = {};
	B.resize(n);

	for(int i=0;i<n;i++) {
		int rev = bit_reverse(i, logn);
		B[i] = A[rev];
	}

	for(int s=1;s<=logn;s++) {
		int m = 1 << s;
		int m2 = m / 2;
		cmx omega = {1, 0};
		cmx pom = {cos(PI / (long double)m), sin(PI / (long double)m)};
		if(num) pom.y = -pom.y;
		for(int j=0;j<m2;j++) {
			for(int k=j;k<n;k+=m) {
				cmx t = omega * B[k + m2];
				cmx u = B[k];
				B[k] = u + t;
				B[k + m2] = u - t;
			}
			omega = omega * pom;
		}
	}

	return B;
}

CI &to_size(CI &A, int size) {
	A.resize(size);
	return A;
}

VI operator *(VI &A, VI &B) {
	CI AC = {};
	CI BC = {};

	for(auto x : A) AC.pb(ll(x));
	for(auto x : B) BC.pb(ll(x));

	int size = A.size() + B.size() - 1;
	int p = 1;
	while(p < size) p *= 2;
	size = p;

	AC = to_size(AC, size);
	BC = to_size(BC, size);

	AC = FFT(AC, false);
	BC = FFT(BC, false);

	CI CC;
	CC.resize(size);
	for(int i=0;i<size;i++) CC[i] = AC[i] * BC[i];

	CC = FFT(CC, true);
	long double t = size;
	
	VI C;
	C.resize(size);
	for(int i=0;i<size;i++) C[i] = round(CC[i].x / t);

	while(C.back() == 0) C.pop_back();

	return C;
}

int main()
{
	VI A = {1, 2};
	VI B = {1, 3};
	VI C = A * B;
	for(auto x : C) cout<<x<<" ";
	return 0;
}
