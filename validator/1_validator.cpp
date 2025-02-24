#include "testlib.h"
#define ll long long
using namespace std;

const int T_MAXN = 1e3;
const int N_MAXN = 10;
const int v_MAXN = 2e8;
const int p_MAXN = 1e9;
const int M_MAXN = 1e5;

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
			inf.readInt(1, v_MAXN);
		}
		else if(type == 2) {
            inf.readSpace();
			inf.readInt(1, p_MAXN);
		}
		else if(type == 3) {
			// pass
		}
		inf.readEoln();
	}

	inf.readEof();
	return 0;
}
