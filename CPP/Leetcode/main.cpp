#include "share.h"

#include <iostream>
using namespace std;
int main() {
    //deduplicate_overlapping();
    //preimageSizeFZF_test();
    //fibonacci_sequence_test();
    int a,b;
    char ch;
    for(int i=0; i<3; i++) {
        while (cin >> a >> ch >> b) {
            cout << "a=" << a << "b=" << b << endl;
            if(!(cin >> ch))break;
        }
    }
    return 0;
}