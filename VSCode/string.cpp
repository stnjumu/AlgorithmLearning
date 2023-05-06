#include"DataStructure/String.h"
#include"DataStructure/array.h"
#include<vector>
#include<iomanip>
#include<assert.h>
#include<algorithm>
#include<unordered_map>
using namespace std;

/*
回文子串(最长或个数)：dp: O(n^2),O(n^2); 双指针中心拓展: O(n^2), O(1); Manacher算法: O(n),O(n);
TODO: O(n)字符串匹配, KMP算法; string库接口：string s, t; int pos = s.find(t); 没找到返回-1;
*/

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

// 3. 无重复字符的最长子串
int lengthOfLongestSubstring(string s) {
    int n=s.length();
    if(n<=1)
        return n;
    
    int ans = 0;
    unordered_map<char, int> char_index;
    int i=0;
    int start=0; // 当前最长子串的left
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
// dp(i,j)定义为s[i, j]是否是回文子串，j>=i;
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
// TODO: 思路3：Manacher算法，O(n) O(n)
// 利用之前遍历过的回文串的长度，可知，遍历一个回文串右边字符时，其在回文串内部的信息与右边对应字符信息有关系；
// 此O(n)算法在n很大且回文串很多时才会体现出来优势；
// * 学习其处理偶数长度子串的做法：在每两个相邻字符间插入#占位符，则可转换为奇数长度子串；abaa -> #a#b#a#a#
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

// 17. 电话号码的字母组合
void back_trace_letterCombinations(vector<string> &digits2Letter, string &digits, int start, vector<string> &ans, string &s) {
    if(start>=digits.length()) {
        ans.push_back(s);
        return;
    }

    char digit = digits[start]-'0'; // ! 字符转数字；
    string letters = digits2Letter[digit];
    for(auto x: letters) {
        s+=x;
        back_trace_letterCombinations(digits2Letter, digits, start+1, ans, s);
        s.pop_back();
    }
}
vector<string> letterCombinations(string digits) {
    if(digits.empty())
        return {};
    vector<string> digits2Letter(10);
    digits2Letter[2]="abc";
    digits2Letter[3]="def";
    digits2Letter[4]="ghi";
    digits2Letter[5]="jkl";
    digits2Letter[6]="mno";
    digits2Letter[7]="pqrs";
    digits2Letter[8]="tuv";
    digits2Letter[9]="wxyz";
    
    vector<string> ans;
    string s;

    back_trace_letterCombinations(digits2Letter, digits, 0, ans, s);
    return ans;
}

// 49. 字母异位词分组
// 法1. 排序。O(nlogn * klogk), 已实现：击败80%, 83%;
// 法2. hash. O(nk)
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<pair<string,string>> strstr;
    for(auto &str:strs) {
        strstr.emplace_back(str, str);
        sort(strstr.back().first.begin(), strstr.back().first.end());
    }
    sort(strstr.begin(), strstr.end(), 
        [](pair<string,string> &a, pair<string,string> &b){
            return a.first<b.first;
        }
    );

    vector<vector<string>> ans;
    string last;
    for(int i=0;i<strstr.size();i++) {
        if(i==0) {
            last = strstr[i].first;
            ans.push_back(vector<string>());
            ans.back().push_back(strstr[i].second);
        }
        else {
            if(strstr[i].first==last) {
                ans.back().push_back(strstr[i].second);
            }
            else {
                last = strstr[i].first;
                ans.push_back(vector<string>());
                ans.back().push_back(strstr[i].second);
            }
        }
    }
    return ans;
}

// 72. 编辑距离
// dp
// dp[i,j]表示w1[0,i]到w2[0,j]的最小编辑距离；
// dp[i,j]= dp[i-1,j-1], w1[i]==w2[j] // 不需要编辑
//        = min(dp[i-1,j-1]+1,  // 替换
//              dp[i-1,j]+1,    // 删除w1[i]，(等价于w2添加w1[i])
//              dp[i,j-1]+1,    // w1添加w2[j], (等价于删除w2[j])
//              ), w1[i] != w2[j] // 需要编辑
// 注意：w1的删除和w2的添加是等价的，同理s2的删除和w1的添加也是等价的，
// 所以就算只提供替换和删除操作(或者替换和添加操作)，本题的做法和递推公式也不会变；
// 但如果只提供删除操作，则递推公式中需要去掉替换那一项；只提供添加操作也一样；
// dp[0,0]依赖于左上角，可以初始化dp[-1,-1]=0, dp[-1,j]=j, dp[i,-1]=i, 其中-1表示空串, dp(-1,-1)表示空串和空串不需要编辑，dp(-1,j)表示空串编辑成w2[0,j]的距离；
// 把上述所有dp下标+1，下标就从0开始了；
int minDistance(string word1, string word2) {
    int m=word1.size(), n=word2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for(int i=0;i<=m;i++) {
        dp[i][0]=i;
    }
    for(int j=0;j<=n;j++) {
        dp[0][j]=j;
    }
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) {
            if(word1[i-1]==word2[j-1]) {
                dp[i][j]=dp[i-1][j-1]; // 不需操作
            }
            else {
                dp[i][j]=min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]})+1; // 操作见上面分析，最终都会是这3个的最小值；
            }
        }
    }
    return dp.back().back();
}

// 76. 最小覆盖子串
// 击败41%, 22%
bool cover(vector<int> &s_count, vector<int> &t_count) {
    for(int i=min('A','a');i<=max('Z','z');++i) {
        if(s_count[i]<t_count[i]) {
            return false;
        }
    }
    return true;
}
string minWindow(string s, string t) {
    vector<int> s_count(256,0);
    vector<int> t_count(256,0);
    for(char c:t) {
        ++t_count[c];
    }

    int ansLen=0;

    int right=0,left=0;
    int bestLeft, bestRight;
    while(right<s.size()) {
        ++s_count[s[right]];

        if(cover(s_count, t_count)) {
            while(t_count[s[left]]<s_count[s[left]]) {
                --s_count[s[left]];
                ++left;
            }
            if(ansLen==0 || ansLen>right-left+1) {
                ansLen = right-left+1;
                bestLeft=left;
                bestRight=right;
            }
        }
    
        ++right;
    }

    if(ansLen!=0)
        return s.substr(bestLeft, bestRight-bestLeft+1);
    else
        return "";
}

// 139. 单词拆分
// 思路1：暴力法
// 思路2：dp
// * s[start, start+size)表示从s[start]开始的长为size的子串，[start, end)表示的串长为end-start, [start, end]表示的串长为end-start+1;
bool backtracingIsMatchWordBreak(string &s, int start, vector<string>& wordDict) {
    if(start == s.length())
        return true;
    
    for(auto &word: wordDict) {
        if(start+word.size()<=s.length()) {
            if(s.substr(start, word.size()) == word) {
                bool flag = backtracingIsMatchWordBreak(s, start+word.size(), wordDict);
                if(flag)
                    return true;
            }
        }
    }
    return false;
}
bool wordBreak1(string s, vector<string>& wordDict) {
    return backtracingIsMatchWordBreak(s, 0, wordDict);
}
// dp; dp[n]表示s[0,n)能够拆分成wordDict;
// dp[i]= 所有word的情况的或, 长为j的word: dp[i-j] && s[i-j, i) == word;
// 显然，所有dp[i]只依赖于dp[i]左边的子问题，可以动态规划，从左到右一遍即可；
// dp[0]=true;
// 击败92%, 90%
bool wordBreak(string s, vector<string>& wordDict) {
    vector<bool> dp(s.length()+1, false);
    dp[0]=true;

    for(int i=0;i<s.size();++i) {
        if(dp[i]) {
            for(string &word:wordDict) {
                if(i+word.size()<=s.length() && dp[i+word.size()]==true) {
                    // 已经可行，不需再判断了；
                    continue;
                }

                if(i+word.size()<=s.length() && s.substr(i, word.size())==word) {
                    dp[i+word.size()]=true;
                }
            }
        }
    }
    return dp[s.length()];
}

// 301.的一个小子问题；
pair<int, int> getLeftRightRemoveOn(string s) {
    // s仅包含()和字母
    // O(n)时间得到s要变成合法括号序列，需要删除的最少的左括号和右括号数；
    int left=0, right=0;
    int i=0;
    while(i<s.size()) {
        if(s[i]=='(') {
            left++;
        }
        else if(s[i]==')') {
            if(left>0)
                left--;
            else
                right++;
        }
        // else 字母，跳过；
        i++;
    }
    return {left, right};
}
// 301. 删除无效的括号
vector<string> backtrace_findans(string &s, int start) {
    // ! 未做完，下面思路有问题，难以实现；
    // TODO: 学习解答；
    int left=0, right=0;
    int i=0;
    while(start+i<s.size() && left>=right) {
        if(s[i]=='(') {
            left++;
        }
        else if(s[i]==')') {
            right++;
        }
        else {
            // 字母
        }
        i++;
    }
    if(start+i<s.size()) {
        // right > left, right==left+1;
        // s[i] == ')'，分割点；
        // s[start, start+i]共i+1个
        string frontHalfPart = s.substr(start, i+1);
    }
    else {
        // left一直>=right; 要删left;
        // 可以正向删括号，反向删左括号；对称的；
    }
}
vector<string> removeInvalidParentheses(string s) {
    return backtrace_findans(s, 0);
}

// 394. 字符串解码
// 递归, 击败100%, 91%
string decodeString(string s) {
    string ans;
    int i=0;
    while(i<s.size()) {
        char c = s[i];
        if(isdigit(c)) {
            int end = i+1;
            while(isdigit(s[end])) {
                end++;
            }
            assert(s[end]=='[');
            string num_s = s.substr(i, end-i);
            int num = stoi(num_s);
            
            // 寻找和[匹配的];
            int str_end = end+1;
            int layer= 1;
            while(layer != 0) {
                if(s[str_end]=='[') {
                    layer++;
                }
                else if(s[str_end]==']') {
                    layer--;
                    if(layer==0) // 最终指向匹配的]
                        break;
                }
                str_end++;
            }
            string decodedStr = decodeString(s.substr(end+1, str_end-end-1));
            for(int j=0;j<num;++j) {
                ans+= decodedStr;
            }

            i = str_end+1;
        }
        else {
            assert(c!='[' && c!=']');
            ans+= c;

            i++;
        }
    }
    return ans;
}

// 438. 找到字符串中所有字母异位词 (子串)
// 滑动窗口，击败93%, 84%
vector<int> findAnagrams(string s, string p) {
    if(s.size()<p.size()) {
        return {};
    }
    // 滑动窗口
    int left=0, right= p.size();
    // 子串：[left, right), len = right - left == p.size();

    vector<int> target(26,0);
    for(int i=0;i<right;++i) {
        target[p[i]-'a']++;
    }
    vector<int> count(26,0);
    for(int i=0;i<right;++i) {
        count[s[i]-'a']++;
    }

    vector<int> ans;
    if(target==count)
        ans.push_back(left);

    while(right<s.size()) { // ! 保证s[right]合法
        // 先迭代再判断，遗漏了最开始的；
        count[s[left]-'a']--;
        left++;
        count[s[right]-'a']++;
        right++;

        if(target==count) {
            ans.push_back(left);
        }
    }

    return ans;
}

// 647. 回文子串
// 思路1：dp, dp[i, j]表示s[i,j]是否回文子串, i<=j; (dp数组只有右上角一半有效)
// dp[i,j] = dp[i+1, j-1] && nums[i]==nums[j]; 
// 假设i向下增大，j向右增大，则dp[i,j]依赖于左下角；
// O(n^2), O(n^2), 击败10%, 50%
// ! 注意此题的时间下界是O(n), 千万别误认为是O(n^2)，注意回文子串是有规律的；
int countSubstrings(string s) {
    int n=s.size();
    if(n<=1)
        return n;
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    // [i,i]
    for(int i=0;i<n;++i) {
        dp[i][i]=true;
    }
    // [i,i+1]
    for(int i=0;i<n-1;++i) {
        dp[i][i+1]= s[i]==s[i+1];
    }

    // [i,i+2]开始，[0, 2]
    // ! 由于依赖于左下角，所以应该一列一列向下计算或一行一行向上计算；(i, j遍历先后顺序问题)
    // 选择一列一列向下
    // for(int j=2;j<n;++j) {
    //     for(int i=0;i<=j-2;++i) { // ! 判断好区间，即i,j遍历范围
    //         dp[i][j] = dp[i+1][j-1] && s[i]==s[j];
    //     }
    // }
    // 选择一行一行向上
    for(int i=n-1;i>=0;--i) {
        for(int j=i+2;j<n;++j) { // ! 判断好区间，即i,j遍历范围
            dp[i][j] = dp[i+1][j-1] && s[i]==s[j];
        }
    }
    // printVectorVector(dp);
    int count = 0;
    for(int i=0;i<n;++i) {
        for(int j=0;j<n;++j) {
            if(dp[i][j])
                count++;
        }
    }
    return count;
}
// 思路2：双指针
// 根据dp分析(画一下求dp矩阵时所有坐标的依赖图)可知，所有dp[i,j]都是从对角线dp[i,i]和dp[i,i+1]向右上递推得到；
// dp[i,i]递推得到的是所有以s[i]为中心的奇数长度回文子串；dp[i,i+1]则是所有偶数长度回文子串，中心则是s[i]和s[i+1]中间；
// O(n^2), O(1), 击败88%, 99%
int countSubstringsOnnO1(string s) {
    int n=s.size();
    if(n<=1)
        return n;
    
    int count = 0;
    int left, right;
    // 奇数长度
    for(int i=0;i<n;++i) {
        left=right=i;
        while(left>=0 && right<n && s[left]==s[right]) {
            count++;
            left--;
            right++;
        }
    }

    // 偶数长度
    for(int i=0;i<n-1;++i) {
        left=i;
        right=i+1;
        while(left>=0 && right<n && s[left]==s[right]) {
            count++;
            left--;
            right++;
        }
    }

    return count;
}
// TODO: 思路3：Manacher算法, 对上面5. 最长回文子串的小改动；
// O(n), O(n);

// 剑指 Offer 05. 替换空格
// 把s中空格换成"%20"
// 思路1：构建新的string, O(n), O(n)，击败27%, 44%
string replaceSpace(string s) {
    string s_new;
    for(char c: s) {
        if(c==' ')
            s_new+="%20";
        else
            s_new+=c;
    }
    return s_new;
}
// * 思路2：原地, 注意技巧；
// 击败100%, 45%
string replaceSpaceOnO1(string s) {
    // 前向统计空格个数
    int count=0;
    for(char c: s) {
        if(c==' ')
            count++;
    }
    if(count>=0) {
        // 预留空间
        int i=s.size()-1;
        s.resize(s.size()+count*2);
        // 反向遍历替换
        int j=s.size()-1;
        while(i>=0) {
            if(s[i]==' ') {
                s[j--]='0';
                s[j--]='2';
                s[j--]='%';
            }
            else {
                s[j--]=s[i];
            }

            --i;
        }
        assert(j==-1);
    }
    return s;
}

// 剑指 Offer 58 - II. 左旋转字符串
// 思路1：O(n), O(k)
// 击败68%, 29%
string reverseLeftWords(string s, int k) {
    // 题目保证k<s.size(), 否则需要取模；
    string temp = s.substr(0, k);
    for(int i=0;i+k<s.size();++i) {
        s[i]=s[i+k];
    }
    copy(temp.begin(), temp.end(), s.end()-k);
    return s;
}
// * 思路2：O(2n), O(1), 击败100%, 99%
string reverseLeftWordsOnO1(string s, int k) {
    // 题目保证k<s.size(), 否则需要取模；
    // * 3次旋转
    reverse(s.begin(), s.end());
    reverse(s.end()-k, s.end());
    reverse(s.begin(), s.end()-k);
    return s;
}

// 剑指 Offer 20. 表示数值的字符串
// O(n), O(1), 击败70%, 50%
bool isFloatOrInt(string &s, int start, int end) {
    if(start>=end)
        return false;
    
    int j=start;
    int digitCount=0;
    // 前导空格
    while(s[j]==' ') {
        j++;
        if(j==end)
            return false;
    }
    // +/-
    if(s[j]=='+'||s[j]=='-') {
        j++;
        if(j==end)
            return false;
    }
    while(j<end) {
        if(!(isdigit(s[j]) || s[j]=='.')) { // ! 好像中间空格不行; 测试样例：". 1"
            return false;
        }
        else if(isdigit(s[j])) {
            digitCount++;
        }
        
        j++;
    }
    return digitCount>0;
}
bool isInt(string &s, int start, int end) {
    if(start>=end)
        return false;
    
    int j=start;
    int digitCount=0;
    // 前导空格
    while(s[j]==' ') {
        j++;
        if(j==end)
            return false;
    }
    // +/-
    if(s[j]=='+'||s[j]=='-') {
        j++;
        if(j==end)
            return false;
    }
    while(j<end) {
        if(!(isdigit(s[j]) || s[j]==' ')) { // ! 不能有'.'，但可以有' '
            return false;
        }
        else if(isdigit(s[j])) {
            digitCount++;
        }
        
        j++;
    }
    return digitCount>0;
}
bool isNumber(string s) {
    // s非空
    int digitCount = 0; // ! 反例"."
    int signCount = 0; // 这个可没有
    int eCount = 0;
    int dotCount = 0;

    // 第一次遍历，确定e的位置
    int i = 0;
    int ePos = -1;
    while(i<s.size()) {
        if(s[i]=='e' || s[i]=='E') {
            ePos = i;
            eCount++;
            if(eCount>1)
                return false;
        }
        else if(s[i]=='.') {
            dotCount++;
            if(dotCount>1)
                return false;
        }
        else if(s[i]=='+' || s[i]=='-') {
            signCount++;
            if(signCount>2)
                return false;
        }
        else if(isdigit(s[i]) || s[i]==' ') { // ! 可以有空格
            digitCount++;
        }
        else {
            // 其他字符
            return false;
        }
        i++;
    }
    if(digitCount==0)
        return false;
    // ! 后置空格可以有，例如"1 "
    while(!s.empty() && s.back()==' ')
        s.pop_back();

    if(ePos == -1) {
        // 无e
        // 只有一个数，可为小数
        return isFloatOrInt(s, 0, s.size());
    }
    else {
        // 有e
        if(ePos == 0 || ePos == s.size()-1)
            return false;
        // 第一个数，可为小数
        // 第二个数, 不能是小数
        return isFloatOrInt(s, 0, ePos) && isInt(s, ePos+1, s.size());
    }
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

    string s_a = to_string(a), s_aa = to_string(aa), s_b = to_string(b), s_bb = to_string(bb); // ! 看样子to_string转换浮点数时也只有7位有效数字，转换整数没有限制；
    cout<< s_a<<" "<<s_aa<<" "<<s_b<<" "<<s_bb<<endl;
    // s_bb只有7位有效数字；
    
    cout<< "基本类型转string: sstream库的ostringstream"<<endl;
    ostringstream oss; // out, 输出用，将其他类型输出到string中; 
    oss << setprecision(15) << bb <<endl; // ? double有效数字有15位，16位不一定准，即前15位保证是准确的；而float有效数字只有6位，前6位保证准确，第7位不一定对；
    string str = oss.str();
    cout<< str<<endl; // ostringstream可保证精度；


    cout<< "string转基本类型: sstream库的istringstream"<<endl;
    istringstream iss(str);
    double new_bb=0.0;
    iss >> new_bb;
    cout<< new_bb<<endl; // 6位
    // 上面的setprecision(15)设置的是oss流的精度；所以这里cout输出new_bb精度还是6位
    cout<< setprecision(15)<<new_bb<<endl; // bb提供的10位, 可保持原精度；

    cout<< s_a<<" "<<s_aa<<" "<<s_b<<" "<<new_bb<<endl;
    a = aa = b = bb = 0;
    a = stoi(s_a); // c++ 11新方法，之前只能用字符数组的atoi等；
    aa = stoll(s_aa);
    b = stof(s_b);
    bb = stod(str); // 没有精度损失；
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

    cout<<"电话号码的字母组合"<<endl;
    vector<string> ans = letterCombinations("23");
    for(string s:ans)
        cout<<s<<" ";
    cout<<endl;

    cout<<"字母异位词分组"<<endl;
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    printVectorString(strs);
    printVectorVectorString(groupAnagrams(strs));

    cout<<"编辑距离"<<endl;
    cout<<minDistance("horse", "ros")<<endl;
    cout<<minDistance("intention", "execution")<<endl;

    cout<<"最小覆盖子串"<<endl;
    cout<<minWindow("ADOBECODEBANC", "ABC")<<endl;
    cout<<minWindow("a", "a")<<endl;
    cout<<minWindow("a", "aa")<<endl;

    cout<<"单词拆分"<<endl;
    strs.assign({"leet", "code"});
    cout<<wordBreak("leetcode", strs)<<endl;
    
    strs.assign({"cats", "dog", "sand", "and", "cat"});
    cout<<wordBreak("catsandog", strs)<<endl;

    cout<<"字符串解码"<<endl;
    cout<<decodeString("3[a]2[bc]")<<endl;
    cout<<decodeString("3[2[bc]]")<<endl;
    // cout<<decodeString("100[leetcode]")<<endl;

    cout<<"找到字符串中所有字母异位词"<<endl;
    printVector(findAnagrams("cbaebabacd", "abc"));
    printVector(findAnagrams("abab", "ab"));

    cout<<"回文子串"<<endl;
    cout<< countSubstrings("abc")<<endl;
    cout<< countSubstrings("aaa")<<endl;
    cout<< countSubstrings("abccba")<<endl;
    cout<< countSubstringsOnnO1("abc")<<endl;
    cout<< countSubstringsOnnO1("aaa")<<endl;
    cout<< countSubstringsOnnO1("abccba")<<endl;

    cout<<"替换空格"<<endl;
    cout<< replaceSpaceOnO1("We are happy")<<endl;
    
    cout<<"左旋转字符串"<<endl;
    cout<< reverseLeftWordsOnO1("abcdefg", 2)<<endl;

    cout<<"表示数值的字符串"<<endl;
    vector<string> numStr = {"+100", "5e2", "-123", "3.1416", "-1E-16", "0123", 
        "12e", "1a3.14", "1.2.3", "+-5", "12e+5.4", "."}; // 第一行6个是，第二行后6个不是
    for(string s: numStr)
        printBool(isNumber(s));

    return 0;
}