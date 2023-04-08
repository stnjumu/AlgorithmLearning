#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 9. 回文数
bool isPalindrome(int x) {
    if(x==0) {
        return true;
    }
    if(x==-2147483648) {
        return false;
    }

    string s=to_string(x);
    int n=s.size();
    for(int i=0;i<n/2;i++) {
        if(s[i]!=s[n-i-1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
        int x;
        cin>>x;
        cout<<isPalindrome(x)<<endl;
    }

    return 0;
}