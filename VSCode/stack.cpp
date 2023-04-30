#include"DataStructure/Array.h"
#include<assert.h>
#include<algorithm>
#include"DataStructure/Stack.h"
#include<unordered_map>
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

// * 单调栈专题 496. 503. 84. 907.
/*//单调栈理解：
遍历过程中，如果一个元素在以后还会用到，我们就需要一个vector存起来；
下一个更大元素这种要求，刚好会使vector中存的元素满足单调性，因为不满足的刚好构成解(弹出是解)或不满足的刚好被覆盖(压入是解)
又因为下一个更大元素的局部性，所有可以实现只看栈顶元素，这样就变成了单调栈；
单调栈相对vector，只会看栈顶O(1)，而vector可以遍历O(n)，所以可以降低复杂度；
*/

// 496. 下一个更大元素I
// 下一个刚好是从左往右的下一个，正序即从左往右，两者顺序相同是“弹出是解”，这种更好写一些；建议示例 3 1 2 4 5 7 6 
vector<int> nextGreaterElementI(vector<int>& nums1, vector<int>& nums2) {
    // 正序，单调递减栈, 击败92%, 45%;
    unordered_map<int, int> next_greater_num;
    stack<int> stack_decrease;
    for(int i=0;i<nums2.size();++i) {
        while(!stack_decrease.empty() && nums2[i]>stack_decrease.top()) { // 维护单调栈
            // * 弹出是解；
            next_greater_num[stack_decrease.top()]=nums2[i]; // 弹出的元素top和nums2[i]刚好构成一组解；top->nums2[i]
            stack_decrease.pop();
        }
        stack_decrease.push(nums2[i]);
    }
    // stack_decrease中剩下的全部没处理，也全是-1;

    for(int i=0;i<nums1.size();++i) {
        auto it = next_greater_num.find(nums1[i]);
        if(it!=next_greater_num.end()) {
            nums1[i]=it->second;
        }
        else {
            nums1[i]=-1;
        }
    }
    return nums1;
}
// 下一个和反序的方向相反，则是"压入是解"，这种方法稍微难写一点点；
// 栈中元素个数则是跟正序/反序时的有序的子序列长度有关，和单调栈的有序顺序相同的子序列长度越大，栈中元素也会更多；但两种方法平均的空间复杂度没有区别；
vector<int> nextGreaterElementI2(vector<int>& nums1, vector<int>& nums2) {
    // 反序，单调递减栈, 和正序用的栈一样；击败92%, 40%
    unordered_map<int, int> next_greater_num;
    stack<int> stack_decrease; 
    int n=nums2.size(); // ! 反序遍历需额外存储int的size，还要特别注意从n-1开始
    for(int i=n-1;i>=0;--i) {
        while(!stack_decrease.empty() && nums2[i]>stack_decrease.top()) { // 维护单调栈
            stack_decrease.pop();
        }
        if(!stack_decrease.empty()) // 非空，则top > nums2[i]; 现在的top和nums2[i]构成一组解: nums2[i]->top; 刚好和正序方法相反；
            next_greater_num[nums2[i]]=stack_decrease.top(); // * 压入是解；
        stack_decrease.push(nums2[i]);
    }
    // 栈中存的大部分是有下一个更大值的，上述没处理的全是-1;

    for(int i=0;i<nums1.size();++i) {
        auto it = next_greater_num.find(nums1[i]);
        if(it!=next_greater_num.end()) {
            nums1[i]=it->second;
        }
        else {
            nums1[i]=-1;
        }
    }
    return nums1;
}

// 503. 下一个更大元素II
// 击败85%, 44%
vector<int> nextGreaterElementsII(vector<int>& nums) {
    // 循环数组；只需要展成[a0, a1, ..., an-1, a0, a1, ..., an-2]，再走一遍单调栈即可；共计算2n-1次；
    // 有重复元素则栈中需要存下标；
    // 建议示例：1 1 2 3 4 3
    vector<int> ans(nums.size(), -1);
    stack<int> stack_decrease;
    for(int i=0;i<nums.size();++i) {
        while(!stack_decrease.empty() && nums[i]>nums[stack_decrease.top()]) { // 维护单调栈
            ans[stack_decrease.top()]=nums[i];
            stack_decrease.pop();
        }
        stack_decrease.push(i);
    }
    for(int i=0;i<nums.size()-1;++i) {
        while(!stack_decrease.empty() && nums[i]>nums[stack_decrease.top()]) { // 维护单调栈
            ans[stack_decrease.top()]=nums[i];
            stack_decrease.pop();
        }
        stack_decrease.push(i);
    }
    return ans;
}

// 556. 下一个更大元素III
// 感觉这题应该是全排列的题，名字一样就放在这里了；两种方法都击败100%, 20%
int nextGreaterElementIII(int n) {
    // 1<=n<=2^31-1;
    // 利用next_permutation算法
    vector<int> nums;
    while(n!=0) {
        nums.push_back(n%10); // 个位在前；
        n/=10;
    }
    reverse(nums.begin(), nums.end());

    if(next_permutation(nums.begin(), nums.end())) {
        long long ans=0;
        for(int i=0;i<nums.size();++i) {
            ans=10*ans+nums[i];
        }
        if(ans<=2147483647)
            return ans;         
    }
    return -1;
}
int nextGreaterElementIII2(int n) {
    // 1<=n<=2^31-1;
    // 利用to_string和stoll；
    string nums = to_string(n); // to_string对整型没有精度损失；特别注意对double有损失，因为to_string转换浮点数只有7位有效数字；

    if(next_permutation(nums.begin(), nums.end())) {
        long long ans= stoll(nums);
        if(ans<= numeric_limits<int>:: max()) // #include<limits>, 等价于INT_MAX, 2147483647
            return ans;
    }
    return -1;
}

// 2454. 下一个更大元素IV，求改元素之后第二个大于它的元素，即第二个更大元素；
// 之前都是求得第一个大于它的元素，现在求第二个
// ! 错误做法：利用下一个更大元素的数组，查找下一个更大元素的下一个更大元素即可；这样求得的是递增子序列的第二个更大元素，实际上不需要连续递增；
// * 正确做法：两个栈，从第一个栈弹出表示找到第一个更大元素，进入第二个栈(可用双端队列)，之后第二个栈再遇到更大元素即第二大元素；这里需注意第二个栈压入顺序；
// 推荐示例: 2 4 0 9 6 和 4 3 10 5 8 1 0 9 2 7 6
vector<int> firstGreaterElement(vector<int> &nums) {
    // 从左到右更大，使用单调递减栈；采用正序，弹出是解；
    // 可能有重复元素，所以栈中存下标；
    vector<int> ans(nums.size(), -1);
    stack<int> decreasingStack; // 存index
    for(int i=0;i<nums.size();++i) {
        while(!decreasingStack.empty() && nums[decreasingStack.top()] < nums[i]) { // 由于弹出是解，当*top和nums[i]相等时，不应弹出，所以只弹出<
            // *top < nums[i], top -> i
            ans[decreasingStack.top()]=i;
            decreasingStack.pop();
        }
        decreasingStack.push(i);
    }

    return ans;
}
// ! 错误做法
vector<int> secondGreaterElementWrong(vector<int>& nums) {
    vector<int> firstGreater = firstGreaterElement(nums);
    printVector(firstGreater);
    vector<int> ans(nums.size(), -1);
    for(int i=0;i<nums.size();++i) {
        if(firstGreater[i] !=-1 && firstGreater[firstGreater[i]])
            ans[i]=nums[ firstGreater[firstGreater[i]] ];
    }
    return ans;
}
vector<int> secondGreaterElement(vector<int>& nums) {
    vector<int> ans(nums.size(), -1);
    stack<int> decreasingStack; // 存index
    // 注意两个栈都应该是单调的；
    stack<int> decreasingStack2, tempStack;
    for(int i=0;i<nums.size();++i) {
        while(!decreasingStack2.empty() && nums[decreasingStack2.top()] < nums[i]) {
            // 发现第二个 *top < nums[i], 解：top -> i, 注意让求的是nums[i]
            ans[decreasingStack2.top()]=nums[i];
            decreasingStack2.pop();
        }

        while(!decreasingStack.empty() && nums[decreasingStack.top()] < nums[i]) { // 由于弹出是解，当*top和nums[i]相等时，不应弹出，所以只弹出<
            // *top < nums[i], top -> i
            tempStack.push(decreasingStack.top());
            decreasingStack.pop();
        }

        while(!tempStack.empty()) {
            // decreasingStack2已经弹出所有小于nums[i]的元素，再压入decreasingStack弹出的所有小于nums[i]的元素，不会破坏其单调性；
            decreasingStack2.push(tempStack.top());
            tempStack.pop();
        }
        decreasingStack.push(i);
    }
    return ans;
}

// 84. 柱状图中最大的矩形
// 求上一个更小元素，单调递增栈，选用正序，两者顺序相反，压入是解；
// 有重复元素，栈存下标；
// 压入是解，且求的是小于，则栈中不应存在指向相同大小值的下标(否则压入时就会形成&n->&n的解)；
vector<int> nextLessPositionLeft(vector<int> &heights) {
    vector<int> ans(heights.size(), -1); // 默认值left=-1
    stack<int> increasingStack;
    for(int i=0;i<heights.size();++i) {
        // 递增栈，所以为了维护单调性，在压入当前元素时应弹出所有>=当前元素的栈顶
        while(!increasingStack.empty() && heights[increasingStack.top()]>=heights[i]) { // 栈中无相等，所以>=都弹出
            increasingStack.pop();
        }
        if(!increasingStack.empty()) {
            ans[i]=increasingStack.top(); // * 压入是解；*top< *i, 所以i -> top
        }
        increasingStack.push(i);
    }
    return ans;
}
// 下一个小于等于元素，单调递增栈，选用正序，两者顺序相同，弹出是解；
// 有重复元素，栈存下标
// 弹出是解，求的是小于等于；所以一样值的应该弹出；
vector<int> nextLessPositionRight(vector<int> &heights) {
    vector<int> ans(heights.size(), heights.size()); // 默认值right=n;
    stack<int> increasingStack;
    for(int i=0;i<heights.size();++i) {
        while(!increasingStack.empty() && heights[increasingStack.top()]>=heights[i]) { // 相等值的应该构成解，所以>=都弹出
            // 弹出是解: *top <= *i, i->top;
            ans[increasingStack.top()]=i;
            increasingStack.pop();
        }
        increasingStack.push(i);
    }
    return ans;
}
// 击败36%, 5%
int largestRectangleArea(vector<int>& heights) {
    vector<int> lefts = nextLessPositionLeft(heights);
    vector<int> rights = nextLessPositionRight(heights);
    // 以heights[i]为最右最小值的最大区间范围为(left, right);
    vector<int> lens(rights.size());
    for(int i=0;i<lens.size();++i) {
        lens[i]= rights[i]-lefts[i]-1;
    }
    // printVector(lefts, "lefts");
    // printVector(rights, "rights");
    // printVector(lens, "lens");
    
    for(int i=0;i<lens.size();++i) {
        lens[i]*= heights[i];
    }
    // printVector(lens, "areas");
    // cout<< *max_element(lens.begin(),lens.end())<<endl;

    return *max_element(lens.begin(),lens.end());

}

// 85. 最大矩形，见Grid_2d.cpp

// TODO: 907. 所有子数组最小元素之和: https://zhuanlan.zhihu.com/p/103562972

// 739. 每日温度
// O(n),O(n), 击败33%, 67%
vector<int> dailyTemperatures(vector<int>& temperatures) {
    // 单调栈简单应用
    // 下一个更高温度(在第几天后)，单调递减栈，从左往右遍历，弹出是解；
    // 要求下标之差，也可能有相同温度，所以使用栈存下标；
    stack<int> stDecreasing;
    vector<int> ans(temperatures.size(), 0);
    for(int i=0;i<temperatures.size();++i) {
        while(!stDecreasing.empty() && temperatures[stDecreasing.top()] < temperatures[i]) {
            // 弹出解：*top < *i
            ans[stDecreasing.top()] = i-stDecreasing.top();
            stDecreasing.pop();
        }
        stDecreasing.push(i);
    }
    return ans;
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

    cout<<"下一个更大元素I"<<endl;
    vector<int> nums1{4,1,2}, nums2{1,3,4,2};
    printVector(nextGreaterElementI2(nums1, nums2));
    nums1.assign({2,4});
    nums2.assign({1,2,3,4});
    printVector(nextGreaterElementI2(nums1, nums2));

    cout<<"下一个更大元素II"<<endl;
    nums1.assign({1,2,1});
    printVector(nextGreaterElementsII(nums1));
    nums1.assign({1,2,3,4,3});
    printVector(nextGreaterElementsII(nums1));

    cout<<"下一个更大元素II"<<endl;
    cout<<nextGreaterElementIII2(12)<<endl;
    cout<<nextGreaterElementIII2(21)<<endl;

    cout<<"下一个更大元素IV: 第二个更大元素"<<endl;
    nums1.assign({2,4,0,9,6});
    printVector(secondGreaterElement(nums1));
    nums1.assign({3,3});
    printVector(secondGreaterElement(nums1));
    nums1.assign({272,238,996,406,763,164,102,948,217,760,609});
    printVector(secondGreaterElement(nums1)); // 406 406 -1 948 -1 217 217 -1 609 -1 -1

    cout<<"柱状图中最大的矩形"<<endl;
    vector<int> heights{2,1,5,6,2,3};
    cout<<largestRectangleArea(heights)<<endl;

    cout<<"每日温度"<<endl;
    nums1.assign({73,74,75,71,69,72,76,73});
    printVector(dailyTemperatures(nums1));

    return 0;
}