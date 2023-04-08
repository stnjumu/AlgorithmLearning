#include<iostream>
#include<vector>

using namespace std;

// 题目有问题，N,M反了；
int main() {
    int N,M,Q;
    cin>>N>>M>>Q;
    vector<int> booksRow(M+1,0); // 0表示未放置，-1表示借走；
    vector<int> locks(N+1, 0);
    for(int i=0;i<Q;i++) {
        int type;
        cin>>type;
        if(type==1) {
            // put book x at row y
            int x, y;
            cin>> x>>y;
            if(booksRow[x] == 0) {
                if(!locks[y]) {
                    booksRow[x]=y;
                }
            }
            else if(booksRow[x]>0) {
                if(!locks[y] && !locks[booksRow[x]])
                    booksRow[x]=y;
            }
            else {
                // 被借走了
            }
        }
        else if(type==2) {
            // row x加锁
            int x;
            cin>>x;
            locks[x]=1;
        }
        else if(type==3) {
            // 去锁
            int x;
            cin>>x;
            locks[x]=0;
        }
        else if(type==4) {
            // 借书x
            int x;
            cin>>x;
            if(booksRow[x]>0) {
                if(locks[booksRow[x]]) {
                    // 上锁
                    cout<<"-1"<<endl;
                }
                else {
                    cout<<booksRow[x]<<endl;
                    booksRow[x]=-1;
                }
            }
            else {
                cout<<"-1"<<endl;
            }
        }
        else if(type==5) {
            // 还书x
            int x;
            cin>>x;
            if(booksRow[x]!=-1) {
                // 书没在小团手中
            }
            else {
                booksRow[x]=0;
            }
        }
    }

    return 0;
}