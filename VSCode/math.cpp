#include"Math/Math.h"
#include"DataStructure/Array.h"
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

// 338. 比特位计数
// 暴力法：击败40%, 11%
int countBitsOfOneNum(int i) {
    int ans = 0;
    while(i!=0) {
        ans += i%2;
        i/=2;
    }
    return ans;
}
vector<int> countBits1(int n) {
    vector<int> ans;
    for(int i=0;i<=n;++i) {
        ans.push_back(countBitsOfOneNum(i));
    }
    return ans;
}
// my数学规律, 2i+1的最后一位B[0]=1, 4i+2, 4i+3的倒数第二位B[1]为0，...
// 更慢了，击败10%, 59%
vector<int> countBits(int n) {
    vector<int> ans(n+1, 0);
    int half = 1;
    while(half <= n) { // half==n也得进循环；
        // 每2half个数，[0, 2half), [2half, 4half) ..., 其中每组的后half个数的倒数第k位为1，所以+1;
        // 其中half = 2^k; 例如half = 1表示每个奇数的最后一位为1, 所以+1;
        int frontHalfFlag = true;
        int i = 0;
        int count = 0;
        while(i<=n) {
            if(frontHalfFlag == false) {
                // 是每组的后half个数；
                ++ans[i];
            }
            ++count;
            if(count==half) {
                count = 0;
                frontHalfFlag = ! frontHalfFlag; // 翻转
            }
            ++i;
        }

        half*=2;
    }
    return ans;
}

// TODO: 理解标答：https://leetcode.cn/problems/counting-bits/solution/bi-te-wei-ji-shu-by-leetcode-solution-0t1i/
// 三种方法都是时间O(n), 空间O(1)，下面只给出了一种示例代码——方法三
// 方法二：dp, 最高有效位；
// 方法三：dp, 最低有效位；
vector<int> countBits3(int n) {
    vector<int> bits(n + 1);
    for (int i = 1; i <= n; i++) {
        bits[i] = bits[i >> 1] + (i & 1);
    }
    return bits;
}
// 方法四：dp, 最低设置位；

// 399. 除法求值
// 击败53%, 79%;
struct UnionFindNode {
    string s;
    double val;
    UnionFindNode* parent;
    UnionFindNode(string _s): s(_s), val(0), parent(NULL) {} // 0 for root
    UnionFindNode(string _s, double _val): s(_s), val(_val), parent(NULL) {}
    UnionFindNode(string _s, double _val, UnionFindNode *_parent): s(_s), val(_val), parent(_parent) {}
};
class UnionFind {
    vector<UnionFindNode*> unionFind;
public:
    UnionFind() {}
    void insert(vector<string> equation, double value) {
        if(equation[0]==equation[1])
            return;
        // union
        UnionFindNode *pA = findNode(equation[0]);
        UnionFindNode *pB = findNode(equation[1]);
        if(pA != NULL && pB!=NULL) {
            // 都已存在，若root不同，则相连；否则不需要做什么；   
            double valueA = 1.0, valueB = 1.0;
            UnionFindNode *pRootA=pA, *pRootB = pB;
            while(pRootA->val!=0) {
                valueA *= pRootA->val;
                pRootA = pRootA->parent;
            }
            while(pRootB->val!=0) {
                valueB *= pRootB->val;
                pRootB = pRootB->parent;
            }
            // pA is root of A, pB is root of B now.
            // 如果两个root相同，则可以计算；
            if(pRootA == pRootB) {
                // A = valueA * A.root, B = valueB * B.root, A = value*B, A.root == B.root;
                assert(valueA = valueB * value);
                return;
            }
            else {
                pRootA -> val = value / valueA;
                pRootA -> parent = pB;
                return;
            }
        }

        if(pB == NULL) {
            // root
            pB = new UnionFindNode(equation[1]);
            unionFind.push_back(pB);
        }
        if(pA == NULL) {
            // not root
            pA = new UnionFindNode(equation[0]);
            unionFind.push_back(pA);
        }
        else {
            // ! 需要考虑同一个A指向多个B的特殊情况；
            if(pA->parent != NULL) { // A 不能再指向B
                // find A.root, and A.root -> B
                double valueA = 1.0;
                while(pA->val!=0) {
                    valueA *= pA->val;
                    pA = pA->parent;
                }
                // A == valueA * A.root
                // A == value * B
                // => A.root = value/valueA * B
                pA -> val = value / valueA;
                pA ->parent = pB;
                return;
            }
        }

        // pA -> pB
        pA->val = value; // ! 必须在这里设置pa.val, 因为有两种情况都要设置：新增A和之前就有A作为root；
        pA->parent=pB;
    }
    UnionFindNode* findNode(string s) {
        for(int i=0;i<unionFind.size();++i) {
            if(unionFind[i]->s==s) {
                return unionFind[i];
            }
        }
        return NULL;
    }
    double find(vector<string> query) {
        // 返回两个数的root和其除以其root的倍数
        UnionFindNode *pA = findNode(query[0]);
        UnionFindNode *pB = findNode(query[1]);
        if(pA == NULL || pB == NULL)
            return -1.0;
        if(query[0]==query[1])
            return 1.0;
        
        double valueA = 1.0, valueB = 1.0;
        while(pA->val!=0) {
            valueA *= pA->val;
            pA = pA->parent;
        }
        while(pB->val!=0) {
            valueB *= pB->val;
            pB = pB->parent;
        }
        // pA is root of A, pB is root of B now.
        // 如果两个root相同，则可以计算；
        if(pA == pB) {
            return valueA / valueB;
        }
        return -1.0;
    }
};
// 优化版本, 简单优化逻辑，击败53%, 96%
// TODO: 还可以优化，find时压缩路径(Path compression):
// 1. p.parent = p.parent.parent 或 2. find(p): p.parent = p.root
// ! 注意本题不好使用weighting, 即长的挂在短的后面，因为此题是有方向的，但硬要做也是可以的。
class UnionFind2 {
    vector<UnionFindNode*> unionFind;
public:
    UnionFind2() {}
    UnionFindNode* findRoot(UnionFindNode* p, double &value) {
        // get p.root, and p = p.root * value;
        value = 1.0;
        while(p->parent!=NULL) {
            value *= p->val;
            p=p->parent;
        }
        return p;
    }
    UnionFindNode* findNode(string s) {
        for(int i=0;i<unionFind.size();++i) {
            if(unionFind[i]->s==s) {
                return unionFind[i];
            }
        }
        return NULL;
    }
    
    void insert(vector<string> equation, double value) {
        if(equation[0]==equation[1])
            return;
        // union
        UnionFindNode *pA = findNode(equation[0]);
        UnionFindNode *pB = findNode(equation[1]);

        if(pB == NULL) {
            // root
            pB = new UnionFindNode(equation[1]);
            unionFind.push_back(pB);
        }
        if(pA == NULL) {
            // not root
            pA = new UnionFindNode(equation[0]);
            unionFind.push_back(pA);
        }

        assert(pA != NULL && pB!=NULL);
        // ! 需要考虑同一个A指向多个B的特殊情况；
        // 都已存在，若root不同，则相连；否则不需要做什么；   
        double valueA = 1.0, valueB = 1.0;
        UnionFindNode *pRootA = findRoot(pA, valueA);
        UnionFindNode *pRootB = findRoot(pB, valueB);
        // pA is root of A, pB is root of B now.
        // 如果两个root相同，则可以计算；
        if(pRootA == pRootB) {
            // A = valueA * A.root, B = valueB * B.root, A = value*B, A.root == B.root;
            assert(valueA = valueB * value);
            return;
        }
        else {
            pRootA -> val = value / valueA;
            pRootA -> parent = pB;
            return;
        }
    }
    double find(vector<string> query) {
        // 返回两个数的root和其除以其root的倍数
        UnionFindNode *pA = findNode(query[0]);
        UnionFindNode *pB = findNode(query[1]);
        if(pA == NULL || pB == NULL)
            return -1.0;
        if(query[0]==query[1])
            return 1.0;
        
        double valueA = 1.0, valueB = 1.0;
        UnionFindNode *pRootA = findRoot(pA, valueA);
        UnionFindNode *pRootB = findRoot(pB, valueB);
        // pA is root of A, pB is root of B now.
        // 如果两个root相同，则可以计算；
        if(pRootA == pRootB) {
            return valueA / valueB;
        }
        return -1.0;
    }
};
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    int n = equations.size();
    assert(n==values.size());

    UnionFind2 uf;
    for(int i=0;i<n;++i) {
        uf.insert(equations[i], values[i]);
    }

    vector<double> ans;
    for(int i=0;i<queries.size();++i) {
        ans.push_back(uf.find(queries[i]));
    }

    return ans;
}

int main() {
    cout<< fastPower(-1.0, -2147483648)<<endl;
    cout<< myPow3(2.0, -2)<<endl;

    for(int i=0;i<100;i++) {
        assert(int(sqrt(i)) == mySqrt(i)); // Nothing happen means mySqrt is right.
        // cout<< i << ","<<mySqrt(i)<<endl;
    }

    cout<<"比特位计数"<<endl;
    printVector(countBits(2));
    printVector(countBits(5));

    cout<<"除法求值"<<endl;
    vector<vector<string>> equations{{"a","b"}, {"b", "c"}};
    vector<double> values{2.0, 3.0};
    vector<vector<string>> queries{{"a", "c"}, {"b", "a"}, {"a","e"}, {"a","a"}, {"x","x"}};
    printVector(calcEquation(equations, values, queries));

    equations.assign({{"a","b"}, {"a", "c"}});
    values.assign({4.0, 2.0});
    queries.assign({{"a", "c"}, {"b", "c"}, {"c","b"}, {"a","a"}, {"x","x"}});
    printVector(calcEquation(equations, values, queries));

    return 0;
}