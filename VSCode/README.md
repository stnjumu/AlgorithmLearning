# cpp环境安装方法

## Win10

### 安装MinGW

https://sourceforge.net/projects/mingw-w64/files/

下载最新版的x86_64-posix-seh即可；
下载后解压缩即可用；得到mingw64文件夹；
复制path\mingw64\bin, (path代指解压到的文件夹)
该bin文件夹中有g++.exe

### 配置环境变量

将path\mingw64\bin填入到Path环境变量中；

### VSCode

VSCode安装C/C++插件
创建个test.cpp文件，编写代码后；
按Ctrl + F5运行，或F5调试；
第一次需要选择环境：g++或gdb; 配置选择: g++.exe