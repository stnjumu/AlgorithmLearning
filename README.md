# AlgorithmLearning

VSCode安装C++环境请看OneNote笔记;

刷算法题推荐VS Code.

## 目前重定向方法

先编译好.exe文件，再手动执行，目前此方法不能测试。

VSCode + Window PowerShell + cpp如何重定向输入输出：(在根目录下)

```powershell
Get-Content input.txt | .\VSCode\test.exe >output.txt
```

VSCode + linux shell + cpp如何重定向输入输出：(在根目录下)

```sh
./VSCode/test.exe <input.txt >output.txt
```

## back_trace 回溯

暂时没有整理，分布于多个cpp文件

常用于遍历，求所有路径，求所有可行方案等问题；这类问题往往需要每个节点都尝试是/否两种情况，一维情况下是O(2^n)种情况；
最重要的是有后效性(前面决策往往会影响后续决策，例如通过一个变量——背包大小等的限制，或者是具体排列、子序列等)，
其次子问题之间相互包含的特点(无最优子结构性质)，只能每个情况都遍历一遍；
往往问题可以变成一个多层决策问题，深层决策是在前面决策的基础上的；循环尝试每个深层决策(深度优先遍历)后，都需要恢复做深层决策之前的状态，称为状态重置(回溯)；

实际上，回溯法就是暴力搜索算法，只是它在构造每个可行解时，每步决策时都重复利用的之前决策获得的中间解(部分解)；

    这里面最重要的方法就是 状态重置 的操作；

分支定界法基于回溯法，只是在每次决策时加上一些上下界的约束；

## dp 动态规划

暂时没有整理，分布于多个cpp文件

常用于求遍历问题中最长、最优、最小的数目或路径的一个解的问题；对于一些无后效性、子问题满足最优子结构性质、且子问题会重复计算的复杂问题；可以用动态规划减少子问题的计算次数，从而降低算法复杂度
