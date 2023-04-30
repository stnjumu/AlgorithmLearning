#include"DataStructure/array.h"
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

// 621. 任务调度器
// 思路1：贪心，每次选剩余次数最多的任务中不在冷却时间的即可；
// 设字母表大小为A, O(A)*O(sort), 由于sort的列表几乎有序，使用quicksort基本都是O(A^2);
// 此题A==26, 实际使用时任务数<A=26;
// 此思路最好O(n*A*logA)，下面实现为O(nA^2), 击败5%, 24%
int leastInterval(vector<char>& tasks, int n) {
    vector<int> taskCount(26, 0);
    for(char task:tasks) {
        taskCount[task-'A']++;
    }

    vector<pair<int, int>> tasksCount2CoolDown;
    auto greater = [](pair<int,int> &a, pair<int,int> &b) {
        return a.first>b.first;
    };
    for(int i=0;i<taskCount.size();++i) {
        if(taskCount[i]>0)
            tasksCount2CoolDown.emplace_back(taskCount[i], 0);
    }
    sort(tasksCount2CoolDown.begin(), tasksCount2CoolDown.end(), greater);
    
    int ans = 0;
    while(!tasksCount2CoolDown.empty()) {
        ans++;
        // 选不在cool down的；
        int j=0;
        while(j<tasksCount2CoolDown.size()) {
            if(tasksCount2CoolDown[j].first>0 && tasksCount2CoolDown[j].second==0) {
                // 选j
                tasksCount2CoolDown[j].first--;
                tasksCount2CoolDown[j].second=n+1;
                break;
            }
            j++;
        }

        // 所有cooldown -1
        for(int k=0;k<tasksCount2CoolDown.size();++k) {
            if(tasksCount2CoolDown[k].second>0)
                tasksCount2CoolDown[k].second--;
        }

        sort(tasksCount2CoolDown.begin(), tasksCount2CoolDown.end(), greater);
        while(!tasksCount2CoolDown.empty() && tasksCount2CoolDown.back().first==0) {
            tasksCount2CoolDown.pop_back();
        }
    }
    return ans;
}
// TODO: 标答;

int main() {
    cout<<"任务调度器"<<endl;
    vector<char> tasks{'A', 'A','A','B','B','B'};
    cout<<leastInterval(tasks, 2)<<endl;
    tasks.assign({'A','A','A','A','A','A','B','C','D','E','F','G'});
    cout<<leastInterval(tasks, 2)<<endl;

    return 0;
}