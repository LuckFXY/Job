#include <iostream>
#include <vector>
using namespace std;
int main() {
	//deduplicate_overlapping();
	//preimageSizeFZF_test();
	//fibonacci_sequence_test();
	vector<vector<int>> dp;
	int cnt = 0;
	for (int i = 0; i<4; i++) {
		dp.emplace_back(vector<int>());
		for (int j = 0; j <= i; j++) {
			dp[i].emplace_back(cnt);
			cnt += 1;
		}
		
	}
	cout << "ok" << endl;
	for (int i = 0; i<4; i++) {
		for (int j = 0; j <= i; j++) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}