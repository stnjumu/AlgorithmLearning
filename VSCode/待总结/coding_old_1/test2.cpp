#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<cassert>
#include<cmath>
#include<cctype>
#include<map>
#include<set>
using namespace std;

int main() {
    vector<int> v{1,2,3,4,5,-1,1,1,1};
    map<int,int,greater<>> count;
    for(int n:v)
        count[n]++;
    for(auto it:count)
        cout<<it.first<<":"<<it.second<<endl;
    
    string s = "abcDEF";
    for(int i=0;i<s.size();i++) {
        s[i]=tolower(s[i]);
    }
    cout<<s<<endl;
    
    cout<<count_if(s.begin(),s.end(), [](int x){return islower(x);})<<endl;

    s.erase(1,2);
    cout<<s<<endl;

    v.erase(v.begin(),v.begin()+1);
    for(auto i:v)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}