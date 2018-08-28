#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ULL;
void num2arr(vector<int>& arr, ULL num) {
	for (int i = 0; i<64; i++) {
		arr[i] = (num & 1) == 0 ? 0 : 1;
		num = num >> 1;
	}
}

int main() {
	ULL x = 0b100100;
	ULL k = 5;
	ULL mask = 1;
	vector<int> candidate(64, 0);
	num2arr(candidate, k);
	int idx = 0;
	for (int i = 0; i<64; i++) {
		if ((x & mask) == 0) {
			if (candidate[idx])
				x = x | mask;
			idx += 1;
		}
		mask = mask << 1;
	}
}