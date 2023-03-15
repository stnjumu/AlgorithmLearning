#include"Math/Math.h"
#include<iostream>
#include<assert.h>
using namespace std;

int main() {
    cout<< fastPower(-1.0, -2147483648)<<endl;
    cout<< myPow3(2.0, -2)<<endl;

    for(int i=0;i<100;i++) {
        assert(int(sqrt(i)) == mySqrt(i)); // Nothing happen means mySqrt is right.
        // cout<< i << ","<<mySqrt(i)<<endl;
    }

    return 0;
}