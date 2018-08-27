#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include<iterator>
using namespace std;

int test_union_set() {
    int n, a;
    cin >> n;
    vector<set<int>> data;
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        flag = false;
        for (auto it = data.begin(); it != data.end(); it++) {
            set<int> &tmp = *it;
            if (tmp.count(i) != 0) {
                flag = true;
                while (cin >> a) {
                    if (a == 0) break;
                    tmp.insert(a);
                }
            }
        }
        if (!flag) {
            set<int> newone;
            newone.insert(i);
            while (cin >> a) {
                if (a == 0) break;
                newone.insert(a);
            }
            data.push_back(newone);
        }
    }
    set<int> res;

    for (auto it = data.begin(); it != data.end(); it++) {
        auto jt = it + 1;
        while(jt != data.end()) {
            res.clear();
            set_intersection((*it).begin(), (*it).end(), (*jt).begin(), (*jt).end(), inserter(res, res.end()));
            if (!res.empty()) {
                (*it).insert((*jt).begin(), (*jt).end());

                jt = data.erase(jt);

            }
            else {
                jt++;
            }
        }

    }
    cout << data.size() << endl;
    return 0;
}