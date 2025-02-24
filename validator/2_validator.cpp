#include "testlib.h"
#define ll long long
using namespace std;

const int T_MAXN = 1e4;
const int N_MAXN = 1e3;
const ll v_MAXN = 2e12;
const ll p_MAXN = 1e13;
const int M_MAXN = 1e8;

int main() {
	registerValidation();

	int T = inf.readInt(1, T_MAXN);
	inf.readSpace();
	inf.readInt(1, M_MAXN);
	inf.readEoln();

	while(T--) {
		int type = inf.readInt(1, 3);
		if(type == 1) {
            inf.readSpace();
			inf.readInt(1, N_MAXN);
			inf.readSpace();
			inf.readLong(1LL, v_MAXN);
		}
		else if(type == 2) {
            inf.readSpace();
			inf.readLong(1LL, p_MAXN);
		}
		else if(type == 3) {
			// pass
		}
		inf.readEoln();
	}

	inf.readEof();
	return 0;
}
