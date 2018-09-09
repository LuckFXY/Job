#include<iostream>
#include<vector>
#include<set>
using namespace std;
struct info{
    long a;
    long b;
    long c;
    info(long ta, long tb, long tc){
        a = ta;
        b = tb;
        c = tc;
    }
    friend bool operator < (const info& a, const info& b);
};
bool operator < (const info& src, const info& dst){
    if(src.a < dst.a && src.b < dst.b && src.c < dst.c)
        return true;

    return false;
}

int unqualified_good(){
    vector<info> data;
    set<int> counter;
    long n,a,b,c;

    while(cin >>n) {

        data.clear();
        int max_i = -1;
        for (int i = 0; i < n; i++) {
            cin >> a >> b >> c;
            data.emplace_back(info(a, b, c));
        }

        for (auto it = data.begin(); it != data.end(); it++) {
            for (auto jt = it+1; jt != data.end(); jt++) {
                if (*it <*jt) {
                    counter.insert(it - data.begin());
                }
            }
        }
        cout << counter.size() << endl;
    }
    return 0;
}

