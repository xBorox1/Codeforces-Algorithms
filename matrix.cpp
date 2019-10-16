#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int DIM = 10;
const long long MOD = 1e9 + 7;
struct Matrix {
	long long tab[DIM][DIM];
	Matrix() {
		for(int i=0;i<DIM;i++)
		for(int j=0;j<DIM;j++) tab[i][j] = 0;
	}
};
Matrix operator *(Matrix &A, Matrix &B) {
	Matrix C;
	for(int i=0;i<DIM;i++)
	for(int j=0;j<DIM;j++)
	for(int k=0;k<DIM;k++)
	C.tab[i][j] = (C.tab[i][j] + A.tab[i][k] * B.tab[k][j]) % MOD;
	return C;
}
Matrix pot(Matrix &A, long long p) {
	if(p == 1) return A;
	Matrix W = pot(A, p / 2);
	W = W * W;
	if(p % 2) W = W * A;
	return W;
}
int main()
{
	return 0;
}
