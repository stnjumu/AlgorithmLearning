#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

// C++中priority_queue是用堆实现的；

void test_heap_algo() {
    vector<int> v = { 3, 5, 2, 6, 8, 1, 0, 4 };
    make_heap(v.begin(), v.end());
    cout << "Heap: ";
    for (auto i : v) cout << i << " ";
    cout << endl;

    v.push_back(7);
    push_heap(v.begin(), v.end()); // 除最后一个元素外是一个堆结构，将最后一个元素插入后修复堆；
    cout << "Heap after push: ";
    for (auto i : v) cout << i << " ";
    cout << endl;

    pop_heap(v.begin(), v.end()); // 将第一个元素和最后一个元素交换位置，则前n-1个值只有第一个节点不满足堆结构，此函数会将前n-1个数修复成堆；
    cout << "Heap after pop: ";
    for (auto i : v) cout << i << " ";
    cout << endl;

    sort_heap(v.begin(), v.end()); // 堆排序；
    cout << "Sorted array: ";
    for (auto i : v) cout << i << " ";
    cout << endl;
}

void my_make_heap(vector<int> &v) {
    // 堆的最优子结构性质，假设L, R是左右子树，已经构成最大堆，root为父节点，则只需将root和左右孩子节点这3个节点调整成堆即可，易证root这个子树是一个堆
    // 所以make_heap只需从底向上构造即可，从最后一个节点的父节点开始，构造子堆结构，然后向左向上遍历其他父节点；
    // ! 只需遍历n/2个父节点，每个父节点只需比较3个数，O(n)复杂度；
    if(v.size()<=1)
        return;

    // 画一个下标从0开始的树，易知(i-1)/2得到父节点坐标，2i+1是左子，2i+2是右子
    int n=v.size();
    for(int i=(n-2)/2;i>=0;i--) {
        int root = v[i];
        
        // 可抽象成函数
        // TODO: 交换3个数

    }
}
void my_push_heap(vector<int> v) {
    // TODO:
    
}
void my_pop_heap(vector<int> v) {
    // TODO:
    
}

void sort_heap_use_pop_heap(vector<int> v) {
    while (!v.empty()) {
        pop_heap(v.begin(), v.end()); // 每次把最大值和最后的元素交换位置，再修复从头插入的n-1个元素的堆；
        cout << v.back() << " ";
        v.pop_back(); // 取出最大值；
    }
}

/*
C++中make_heap实现, 来自new bing；
template <class RandomAccessIterator>
void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    if (last - first < 2) return;
    auto n = last - first;
    for (auto i = n / 2; i >= 1; --i) {
        auto k = i;
        auto v = *(first + k - 1);
        auto heap = false;
        while (!heap && 2 * k <= n) {
            auto j = 2 * k;
            if (j < n) {
                if (*(first + j - 1) < *(first + j)) ++j;
            }
            if (v >= *(first + j - 1)) heap = true;
            else {
                *(first + k - 1) = *(first + j - 1);
                k = j;
            }
        }
        *(first + k - 1) = v;
    }
}
*/