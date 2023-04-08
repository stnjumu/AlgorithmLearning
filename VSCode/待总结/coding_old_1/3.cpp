#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

// 205. 同构字符串
bool isIsomorphic(string s, string t) {
    unordered_map<char,char> maps1,maps2;
    int n=s.size();
    if(n<=1) {
        return true;
    }

    for(int i=0;i<n;i++) {
        if(maps1.find(s[i])!=maps1.end()) {
            // found
            if(maps1[s[i]]!=t[i])
                return false;
        }
        else {
            maps1[s[i]]=t[i];
        }
        
        if(maps2.find(t[i])!=maps2.end()) {
            // found
            if(maps2[t[i]]!=s[i])
                return false;
        }
        else {
            maps2[t[i]]=s[i];
        }
    }
    return true;
}

int main() {
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
        string a,b;
        cin>>a>>b;
        cout<<isIsomorphic(a,b)<<endl;
    }

    return 0;
}