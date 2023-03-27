#include"DataStructure/String.h"
#include<vector>
#include<iomanip>
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
}