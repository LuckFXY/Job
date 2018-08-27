#include <iostream>
#include <vector>
#include<map>
#include<set>
using namespace std;

int main() {
    int n, m, idx;
    cin >> n >> m;
    vector<int> data(m+1,0);
    for (int i = 1; i <= n; i++) {
        cin >> idx;
        data[idx] = 1;
    }
    cin >> n;

    int left, right;
    set<int> ret;
    for (int i = 0; i < n; i++) {
        cin >> left >> right;
        ret.clear();
        for (int j = left; j <= right; j++) {
            if (data[j] == 1)
                ret.insert(j);
        }
        cout << ret.size() << endl;
    }
    return 0;
}