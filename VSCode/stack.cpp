#include"DataStructure/Array.h"
#include<assert.h>
#include<algorithm>
#include"DataStructure/Stack.h"
using namespace std;

// 剑指 Offer 09. 用两个栈实现队列
class CQueue {
    stack<int> s1, s2;
    void moveS1ToS2() {
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }
public:
    CQueue() {

    }
    
    void appendTail(int value) {
        s1.push(value);
    }
    
    int deleteHead() {
        if(s2.empty()) {
            moveS1ToS2();
        }

        if(s2.empty()) {
            return -1;
        }
        else {
            int temp = s2.top();
            s2.pop();
            return temp;
        }
    }
};

// 20. 有效的括号
bool bracketsIsValid(string s) {
    stack<char> st;

    auto match = [](char a, char b) {
        return a=='('&&b==')' || a=='['&&b==']' || a=='{'&&b=='}';
    };

    for(auto c: s) {
        if(c=='('||c=='['||c=='{') {
            st.push(c);
        }
        else {
            if(!st.empty() && match(st.top(), c)) { // ! 注意st可能为空，则不匹配；
                st.pop();
            }
            else {
                return false;
            }
        }
    }

    if(st.empty())
        return true;
    else
        return false;
}

// 22. 括号生成
void back_trace_generateParenthesis(vector<string> &ans, int pushTime, int popTime, string &s) {
    if(pushTime==0 && popTime==0) {
        ans.push_back(s);
        return;
    }

    if(pushTime>0) {
        s+='(';
        back_trace_generateParenthesis(ans, pushTime-1, popTime+1, s);
        s.pop_back();
    }
    if(popTime>0) {
        s+=')';
        back_trace_generateParenthesis(ans, pushTime, popTime-1, s);
        s.pop_back();
    }
}
vector<string> generateParenthesis(int n) {
    vector<string> ans;
    string s;
    back_trace_generateParenthesis(ans, n, 0, s);
    return ans;
}

// 32. 最长有效括号
// ! 错误，无法统计()()()
int __Wrong_longestValidParentheses(string s) {
    int ans=0;
    int maxAns =0;

    stack<int> stk;
    int i = 0;
    while(i < s.length()) {
        if(s[i]=='(')
            stk.push(0);
        else { // ')'
            if(stk.empty()) { // not match
                ans=0;
            }
            else {
                ans = stk.top();
                stk.pop();
                ans+=2;
                if(!stk.empty())
                    stk.top()+=ans;
                else
                    maxAns=max(maxAns, ans);
            }
        }

        i++;
    }
    while(!stk.empty()) {
        if(stk.top()>maxAns)
            maxAns=stk.top();
        stk.pop();
    }
    return maxAns;
}
// 击败76%, 36%
// 我这种方法是基于stack的，O(n),O(n); 还有动态规划O(n),O(n)和左右括号计数的O(n),O(1): https://leetcode.cn/problems/longest-valid-parentheses/solution/zui-chang-you-xiao-gua-hao-by-leetcode-solution/
// 我的方法是栈中压入当前最长的长度，还可以压入(的下标，这样出栈时可以直接计算长度；
int longestValidParentheses(string s) {
    int maxAns =0;

    stack<int> stk;
    stk.push(0); // 提前压入0来统计后面所有括号的加和；

    int i = 0;
    while(i < s.length()) {
        if(s[i]=='(')
            stk.push(0);
        else { // ')'
            if(stk.size()>1) { // 提前压入0，记录ans；所以s.size()>1表示栈非空
                int ans = stk.top();
                stk.pop();
                ans+=2;
                stk.top()+=ans;
            }
            else {
                // not match, 之前统计的长度可以清0了；
                if(stk.top()>maxAns)
                    maxAns=stk.top();
                stk.top()=0;
            }
        }

        i++;
    }
    while(!stk.empty()) {
        if(stk.top()>maxAns)
            maxAns=stk.top();
        stk.pop();
    }
    return maxAns;
}

// 856. 括号的分数
int scoreOfParentheses(string s) {
    stack<int> stk;
    stk.push(0);

    for(auto c: s) {
        if(c=='(') {
            stk.push(0);
        }
        else {
            assert(stk.size()>1);
            if(stk.top()==0) {
                stk.pop();
                stk.top()+=1;
            }
            else {
                int temp = stk.top()*2;
                stk.pop();
                stk.top()+=temp;
            }
        }
    }
    return stk.top();
}

int main()
{
    cout<<"最小栈"<<endl;
    MinStack s;
    s.push(-2);
    s.push(0);
    s.push(-3);
    cout<<s.getMin()<<endl; // -3
    s.pop();
    cout<<s.top()<<endl; // 0
    cout<<s.getMin()<<endl; // -2

    cout<<"两个栈实现队列"<<endl;
    CQueue cq;
    cq.appendTail(3);
    cout<<cq.deleteHead()<<endl; // 3
    cout<<cq.deleteHead()<<endl; // -1
    cout<<cq.deleteHead()<<endl; // -1

    cq.appendTail(5);
    cq.appendTail(2);
    cout<<cq.deleteHead()<<endl; // 5
    cout<<cq.deleteHead()<<endl; // 2

    cout<<"有效的括号"<<endl;
    cout<< bracketsIsValid("()")<<endl;
    cout<< bracketsIsValid("()[]{}")<<endl;
    cout<< bracketsIsValid("(]")<<endl;

    cout<<"括号生成"<<endl;
    printVector(generateParenthesis(3));
    printVector(generateParenthesis(1));

    cout<<"最长有效括号"<<endl;
    cout<<longestValidParentheses("(()")<<endl;
    cout<<longestValidParentheses(")()())")<<endl;
    cout<<longestValidParentheses("")<<endl;
    cout<<longestValidParentheses("(((())(())()()(()()()()(())(")<<endl;

    cout<<"括号的分数"<<endl;
    cout<<scoreOfParentheses("()")<<endl;
    cout<<scoreOfParentheses("()()")<<endl;
    cout<<scoreOfParentheses("(())")<<endl;
    cout<<scoreOfParentheses("((())())()")<<endl;

    return 0;
}