#include"DataStructure/String.h"
#include<vector>
#include<iomanip>
#include<assert.h>
#include<unordered_map>
using namespace std;

void back_trace_binary_watch(int turnedOn, int start, vector<int> &hours, vector<int> &minutes, vector<string> &ans) {
    // start: 0-3表示小时，4以上表示分钟;
    if(turnedOn == 0) {
        string time;
        int hour = 0, minute = 0;
        for(int i=0, h = 8;i<hours.size();i++,h/=2) // 时间计算方法不错；
            hour += hours[i]* h;
        for(int i=0, m = 32;i<minutes.size();i++, m/=2)
            minute += minutes[i]*m;
        
        if(hour>11||minute>59) // ! 不合法时间;
            return;

        time.append(to_string(hour));
        time.append(":");
        if(minute<10)
            time.append("0");
        time.append(to_string(minute));

        ans.push_back(time);
        return;
    }
    if(start<10) {
        // 第start个灯亮, 插入1
        if(start<=3)
            hours.push_back(1);
        else
            minutes.push_back(1);
        back_trace_binary_watch(turnedOn-1, start+1, hours, minutes, ans);
        if(start<=3)
            hours.pop_back();
        else
            minutes.pop_back();
        
        // 第start个灯不亮, 插入0
        if(start<=3)
            hours.push_back(0);
        else
            minutes.push_back(0);
        back_trace_binary_watch(turnedOn, start+1, hours, minutes, ans);
        if(start<=3)
            hours.pop_back();
        else
            minutes.pop_back();
    }

}
// 401. 二进制手表
vector<string> readBinaryWatch(int turnedOn) {
    vector<string> ans;
    vector<int> hours, minutes;
    back_trace_binary_watch(turnedOn, 0, hours, minutes, ans);
    return ans; // 一定记得ret；
}

// 3. 无重复字符的最长字串
int lengthOfLongestSubstring(string s) {
    int n=s.length();
    if(n<=1)
        return n;
    
    int ans = 0;
    unordered_map<char, int> char_index;
    int i=0;
    int start=0; // 当前最长字串的left
    int count=0; // right = left + count
    while(i<n) {
        char c = s[i];
        if(char_index.find(c)==char_index.end()) {
            // 没找到重复的
            count++;
            char_index[c]=i;
        }
        else {
            // 找到;
            if(ans<count)
                ans=count;
            // 更新start和char_index
            for(int j = start;j<char_index[c];j++) {
                char_index.erase(s[j]);
            }
            start = char_index[c]+1;
            count = i-start+1;
            char_index[c]=i;
        }
        i++;
    }
    // ! 最后一个值也需要考察；一定要思考开始条件和终止条件；
    if(ans<count)
        ans = count;

    return ans;
}

// 5. 最长回文子串
// 思路1： 动态规划 O(n^2), O(n^2)
// dp(i,j)定义为s[i, j]是否是回文字串，j>=i;
// dp(i,j)=dp(i+1, j-1) && s[i]==s[j]，依赖于右下角；
// dp(i,i)和dp(i,i+1)易知, 根据两种可往左上角进行递推；
string longestPalindrome(string s) {
    if(s.size()<=1) {
        return s;
    }

    vector<bool> v;
    v.assign(s.size(), false);
    vector<vector<bool>> dp;
    dp.assign(s.size(), v);
    
    for(int i=1;i<s.size();i++) {
        dp[i][i]=true;
        dp[i-1][i]=s[i-1]==s[i];
    }
    dp[0][0]=true;

    for(int j=1;j<s.size();j++) {
        for(int i=0;i<j-1;i++) {
            dp[i][j]=dp[i+1][j-1] && s[i]==s[j];
        }
    }
    
    // find longest.
    int maxLen = 1;
    int maxi=0;
    for(int j=0;j<s.size();j++) {
        for(int i=0;i<=j;i++) {
            if(dp[i][j] && j-i+1>maxLen) {
                maxi=i;
                maxLen=j-i+1;
            }
        }
    }
    return s.substr(maxi, maxLen);
}
// 思路2：中心扩展算法 O(n^2), O(1)
// 所有dp[i,j]只与dp[i+1,j-1]有关，即形成斜向左上的依赖链，我们只需要遍历每个dp[i,i]和每个dp[i,i+1]，向左上角递推即可求得所有dp[i,j]
    // 实际上，不需要保存所有dp[i,j]，只需保存当前最长的即可。
string longestPalindrome2(string s) {
    // 比上面的思路1的快很多，内存也小很多。
    int n = s.size();
    if(n<=1)
        return s;

    int maxLen=1;
    int maxLeft=0;
    // 奇数串
    for(int i=0;i<n;i++) {
        int len = 1;
        // dp[i,i] -> dp[i-x, i+x], i-x >=0;
        for(int j=i-1;j>=0;j--) { // [i-x, i+x] == [j, 2i-j]
            if(2*i-j < n && s[j]==s[2*i-j]) {
                len+=2;
                if(len>maxLen) {
                    maxLen=len;
                    maxLeft=j;
                }
            }
            else
                break;
        }
    }

    // 偶数串
    for(int i=0;i<s.size();i++) {
        int len=0;
        // dp[i, i+1] -> dp[i-x, i+1+x]
        for(int x=0;x<=i;x++) {
            if(i+1+x<n && s[i-x]==s[i+1+x]) {
                len+=2;
                if(len>maxLen) {
                    maxLen=len;
                    maxLeft=i-x;
                }
            }
            else
                break;
        }
    }
    return s.substr(maxLeft, maxLen);
}
// 思路3：Manacher算法，O(n) O(n)
// 利用之前遍历过的回文串的长度，可知，遍历一个回文串右边字符时，其在回文串内部的信息与右边对应字符信息有关系；
// https://leetcode.cn/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-by-leetcode-solution/

// 10. 正则表达式匹配
// dp[i,j]表示s前i项和p前j项匹配，i>=0,j>=0
// dp[i,j]= {
//      dp[i,j-2] || dp[i-1,j],     p[j]=='*' and p[j-1]==s[i]  // 对应用/不用
//      dp[i,j-2],                  p[j]=='*' and p[j-1]!=s[i]
//      dp[i-1,j-1],                p[j]=='.'
//      dp[i-1,j-1]&&s[i]==p[j],    others.
// }
// 画二维i,j的依赖表格，可知dp[i,j]只依赖于左下方的dp值，所以可以迭代解决；
// 为了计算方便，可以定义dp[-1,-1]=true；为了C++表示方便，可将定义dp (m+1)*(n+1), 则i,j坐标改成从1开始；
bool isMatch(string s, string p) {
    // a . *
    int m=s.size(), n=p.size();
    if(m==0&&n==0) {
        return true;
    }
    assert(p[0]!='*');

    vector<bool> v;
    v.assign(n+1, false);
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    // vector<vector<bool>> dp;
    // dp.assign(m+1, v);
    // dp[0][0]=true; // 多一个0,0利于计算；
    s= '#'+s;
    p= '#'+p;

    for(int j=1;j<=n;j++) {
        for(int i=0;i<=m;i++) { // ! 特别注意i从0开始，见样例s="aab",p="c*a*b"
            if(p[j]=='*') {
                if(p[j-1]=='.' || p[j-1]==s[i]) {
                    // dp[i][j]=dp[i][j-2] || (i>0 &&dp[i-1][j]) || (i>0 &&dp[i-1][j-2]); // 不用/用/用一次
                    dp[i][j]=dp[i][j-2] || (i>0 &&dp[i-1][j]); // ! 用一次显然能被用和不用的组合替代；不用/用
                }
                else {
                    dp[i][j]=dp[i][j-2];
                }
            }
            else if(p[j]=='.') {
                dp[i][j]=(i>0 &&dp[i-1][j-1]);
            }
            else {
                dp[i][j]=(i>0 && dp[i-1][j-1]&&s[i]==p[j]);
            }
        }
    }
    return dp.back().back();
}
// 标答：优化了i>0的判断，抽象了matches方法
bool isMatch2(string s, string p) {
    int m = s.size();
    int n = p.size();

    auto matches = [&](int i, int j) { // ! 将复杂的判断匹配过程抽象，lambda表达式；我就是因为判断s和p的位置时坐标需要-1才将s,p前面加了个字符；这里把-1放在了函数中，避免写错；
        if (i == 0) {
            return false;
        }
        if (p[j - 1] == '.') {
            return true;
        }
        return s[i - 1] == p[j - 1];
    };

    vector<vector<int>> f(m + 1, vector<int>(n + 1));
    f[0][0] = true;
    for (int i = 0; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                f[i][j] |= f[i][j - 2]; // ! 这句在判断match之前做，可以应对i=0时遇到x*的情况。
                // 分析p[j-1]=='*'的两种情况可优化成这样；
                if (matches(i, j - 1)) {
                    f[i][j] |= f[i - 1][j];
                }
            }
            else {
                if (matches(i, j)) {
                    f[i][j] |= f[i - 1][j - 1];
                }
            }
        }
    }
    return f[m][n];
}

int main() {
    cout<< "基本类型转string: to_string"<<endl; // c++ 11新方法；
    // 常值后缀: u/U表示整型的无符号，ll/LL表示long long；f/F表示float; 由于常量默认是int和double类型，所以这3个就够用了；
    int a = 1;
    long long aa= 2147483649LL; // ! 注意long 等价于 int
    float b = 1.1F;
    double bb = 3.141592654; // ! C++ long double等价于double, long float 等价于 double;
    // 基本常用就这4种基本数值类型：int, long long; float, double; 没有表示范围更大的内置基本类型了，更多请考虑gcc拓展的__int128, GMP包等，或者自己实现相应位数的整型(一般硬件支持才能更快，否则只能模拟，速度很慢)；
    cout<< a<<" "<<aa<<" "<<b<<" "<<bb<<endl; // ! cout输出浮点数默认6位有效数字; 因为float有效数字只有6位
    // cout << setprecision(4)<< bb<<endl; // 设置精度, 一直有效; #include <iomanip> //需要包含的头文件
    // cout << fixed << setprecision(4) << bb << endl; // fixed表示按小数点后保留4位小数，没有fixed则是4位有效数字；一直有效；
    // cout.unsetf(ios::fixed); // 取消fixed;
    // cout.precision(6); // 恢复默认精度;

    string s_a = to_string(a), s_aa = to_string(aa), s_b = to_string(b), s_bb = to_string(bb); // ! 看样子to_string也只有7位有效数字；
    cout<< s_a<<" "<<s_aa<<" "<<s_b<<" "<<s_bb<<endl;
    // s_bb只有7位有效数字；

    
    cout<< "基本类型转string: sstream库的ostringstream"<<endl;
    ostringstream oss; // out, 输出用，将其他类型输出到string中; 
    oss << setprecision(15) << bb <<endl; // ? double有效数字有15位，16位不一定准，即前15位保证是准确的；而float有效数字只有6位，前6位保证准确，第7位不一定对；
    string str = oss.str();
    cout<< str<<endl;


    cout<< "string转基本类型: sstream库的istringstream"<<endl;
    istringstream iss(str);
    double new_bb=0.0;
    iss >> new_bb;
    cout<< new_bb<<endl; // 6位
    cout<< setprecision(15)<<new_bb<<endl; // bb提供的10位

    a = aa = b = bb = 0;
    a = stoi(s_a); // c++ 11新方法，之前只能用字符数组的atoi等；
    aa = stoll(s_aa);
    b = stof(s_b);
    bb = stod(s_bb); // 7位有效数字；
    cout<< a<<" "<<aa<<" "<<b<<" "<<bb<<endl; // 之前设置了15位有效数字；



    cout<< "二进制手表"<<endl;
    printVectorString(readBinaryWatch(1));
    printVectorString(readBinaryWatch(9));

    cout<<"无重复字符的最长子串"<<endl;
    cout<<lengthOfLongestSubstring("abcabcbb")<<endl;
    cout<<lengthOfLongestSubstring("bbbbb")<<endl;
    cout<<lengthOfLongestSubstring("pwwkew")<<endl;

    cout<<"最长回文子串"<<endl;
    cout<<longestPalindrome("babad")<<endl;
    cout<<longestPalindrome("cbbd")<<endl;

    cout<<"最长回文子串2"<<endl;
    cout<<longestPalindrome2("babad")<<endl;
    cout<<longestPalindrome2("cbbd")<<endl;

    cout<<"正则表达式匹配"<<endl;
    cout<<isMatch("aa","a")<<endl;
    cout<<isMatch("aa","a*")<<endl;
    cout<<isMatch("ab",".*")<<endl;
    cout<<isMatch("aabbcc","a*b*c.")<<endl;
    cout<<isMatch("aab","c*a*b")<<endl;

    return 0;
}