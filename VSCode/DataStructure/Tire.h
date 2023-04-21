#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<cassert>
using namespace std;

struct TrieNode {
    char val;
    bool isNull;
    vector<TrieNode*> children;
    TrieNode():val(0), isNull(true) {}
    TrieNode(char _val): val(_val), isNull(false) {}
    void clear() {
        for(TrieNode* child: children) {
            child->clear(); // 递归clear
            delete child; // 回收空间；
        }
        children.clear();
    }

    TrieNode *getChild(char val) {
        for(TrieNode* child: children) {
            if(child->val == val) {
                return child;
            }
        }
        return NULL;
    }
    void addChild(TrieNode *_child) {
        children.push_back(_child);
    }
    bool isWordBack() {
        for(auto child:children) {
            if(child->isNull)
                return true;
        }
        return false;
    }
};
// 使用多叉树+nullNode做为End标志；击败22%, 96%
// 注意：仅apple，则查找app返回false, 查找前缀app返回true
// 但插入apple和app, 则查找app返回true；
// 改进点：不使用nullNode，直接在最后一个字母上标记isWordBack;
class Trie {
private:
    TrieNode *rootNull;

public:
    Trie() {
        rootNull = new TrieNode(char(0));
    }
    ~Trie() {
        rootNull->clear();
        delete rootNull;
        rootNull = NULL;
    }
    
    void insert(string word) {
        TrieNode *p = rootNull;
        int i=0;
        while(i<word.length()) {
            char c = word[i];
            assert(c!=0); // 不支持

            TrieNode *child = p->getChild(c);
            if(child!=NULL) {
                // 存在
                p = child;
            }
            else {
                // 不存在
                break;
            }
            i++;
        }
        while(i<word.length()) {
            // word[i]即之后不存在；
            // 依次插入到p子树中；
            TrieNode *child = new TrieNode(word[i]);
            p->addChild(child);
            p=child;
            i++;
        }
        // 插入结束符；
        TrieNode *null =new TrieNode();
        p->addChild(null);
    }
    
    bool search(string word) {
        TrieNode *p = rootNull;
        int i=0;
        while(i<word.length()) {
            char c = word[i];
            assert(c!=0); // 不支持

            TrieNode *child = p->getChild(c);
            if(child!=NULL) {
                // 存在
                p = child;
            }
            else {
                // 不存在
                break;
            }
            i++;
        }
        if(i==word.length()) {
            // 字符串已消耗完；如果p刚好指向叶子节点，则找到；
            if(p->isWordBack())
                return true;
        }
        return false;
    }
    
    bool startsWith(string prefix) {
        TrieNode *p = rootNull;
        int i=0;
        while(i<prefix.length()) {
            char c = prefix[i];
            assert(c!=0); // 不支持

            TrieNode *child = p->getChild(c);
            if(child!=NULL) {
                // 存在
                p = child;
            }
            else {
                // 不存在
                break;
            }
            i++;
        }
        if(i==prefix.length()) {
            return true;
        }
        return false;
    }

    void printLayerOrder(string name="Trie") {
        cout<< name<<"= "<<endl;
        cout<< "Root"<<endl;
        queue<TrieNode*> st;
        for(TrieNode *child: rootNull->children) {
            st.push(child);
        }
        while(!st.empty()) {
            int layerLen = st.size();
            for(int i=0;i<layerLen;++i) {
                TrieNode *node = st.front();
                st.pop();

                if(!node->isNull)
                    cout<<node->val<<" ";
                else
                    cout<<"null"<<" ";
                for(TrieNode *child: node->children) {
                    st.push(child);
                }
            }
            cout<<endl;
        }
    }
};