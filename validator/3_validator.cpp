#include "testlib.h"
#define ll long long
using namespace std;

const int T_MAXN = 1e6;
const int N_MAXN = 1e6;
const ll v_MAXN = 1e18;
const ll p_MAXN = 2e18;
const ll M_MAXN = 1e12;

int main() {
	registerValidation();

	int T = inf.readInt(1, T_MAXN);
	inf.readSpace();
	inf.readLong(1LL, M_MAXN);
	inf.readEoln();

	while(T--) {
		int type = inf.readInt(1, 3);
        ensure(type == 1 or type == 2);
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
