#include"DataStructure/Array.h"
#include<algorithm>

using namespace std;

// 48. 旋转图像
// 向右旋转90°
// 法一：分块法：将图像分成不重合的4块，左上、右上、右下、左下；需要分n的奇偶且特别注意边界情况；
// 法二：上下对称+转置 或转置+左右对称；二倍于法一计算量；
// 补充：旋转180°= 上下翻转再左右翻转； 向左旋转90°=左右翻转+转置= 转置+上下翻转；
// ! 特别注意转置和翻转不可交换；推荐先转置，再观察后续翻转变化；
// ! 注意图像中一般左上角是[0,0]位置，向下是x变大，向右是y变大；
void rotateRight90(vector<vector<int>>& matrix) {
    // 法二: 转置+左右对称
    int n=matrix.size();
    if(n<=1)
        return;
    
    for(int i=0;i<n;i++) {
        for(int j=0;j<i;j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<n/2;j++) {
            swap(matrix[i][j], matrix[i][n-1-j]);
        }
    }
}

int main() {
    vector<vector<int>> matrix{{{1,2,3},{4,5,6},{7,8,9}}};
    printVectorVector(matrix);
    rotateRight90(matrix);
    printVectorVector(matrix);

    return 0;
}