#pragma once

#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;


void printVector(vector<int> v, string name = string("Vector")) {
	cout << name << " = ";
	for (auto n : v)
		cout << n << " ";
	cout << endl;
}

void vectorLearning() {
	cout << "vector基本方法" << endl;
	vector<int> a, b{ 1,2,3,4,5 };
	//a含有4个值为2的元素
	a.assign(4, 2);
	printVector(a);
	//b为向量，将b的0-2个元素赋值给向量a
	a.assign(b.begin(), b.begin() + 3);
	printVector(a);

	//返回a的最后一个元素
	cout << a.back() << endl;

	//返回a的第一个元素
	cout << a.front() << endl;

	//清空a中的元素
	a.clear();
	printVector(a);

	//判断a是否为空，空则返回true，非空则返回false
	cout << a.empty() << endl;

	//在a的最后一个向量后插入一个元素，其值为5
	a.push_back(5);
	a.push_back(10);
	printVector(a);

	//删除a向量的最后一个元素
	a.pop_back();
	printVector(a);

	//删除a中第一个（从第0个算起）到第二个元素，也就是说删除的元素从a.begin()+1算起（包括它）一直到a.begin()+3（不包括它）结束
	a.assign({ 1,2,3,4,5,6 });
	a.erase(a.begin() + 1, a.begin() + 3);
	printVector(a);

	//在a的第一个元素（从第0个算起）位置插入数值5,
	a.assign({ 1,2,3,4,5,6 });
	a.insert(a.begin() + 1, 5);
	printVector(a);

	//在a的第一个元素（从第0个算起）位置插入3个数，其值都为5
	a.assign({ 1,2,3,4,5,6 });
	a.insert(a.begin() + 1, 3, 5);
	printVector(a);

	// b为容器或b为数组，以迭代器作为参数，插入两迭代器之间元素；
	a.assign({ 1,2,3,4,5,6 });
	a.insert(a.begin() + 1, b.begin() + 1, b.begin() + 3);
	printVector(a);

	//将a的现有元素个数调整至10个，多则删，少则补，其值随机
	a.resize(10);
	printVector(a);
	//返回a中元素的个数
	cout << a.size() << endl;
	//返回a在内存中总共可以容纳的元素个数
	cout << a.capacity() << endl;

	//将a的现有元素个数调整至n个，多则删，少则补，其值为2
	a.resize(15, 2);
	printVector(a);
	a.resize(5, 2);
	printVector(a);

	//将a的容量扩充至100，
	a.reserve(100);
	cout << a.capacity() << endl;

	//b为向量，将a中的元素和b中的元素整体交换
	a.swap(b);
	printVector(a);
	printVector(b);

	// ?? b为向量，向量的比较操作还有 != >= > <= <
	// a==b

	cout << "vector常用算法" << endl;
	//对a中的从a.begin()（包括它）到a.end()（不包括它）的元素进行从小到大排列
	a.assign({ 2,3,5,6,4,1 });
	sort(a.begin(), a.end());
	printVector(a);

	//对a中的从a.begin()（包括它）到a.end()（不包括它）的元素倒置，但不排列，如a中元素为1,3,2,4,倒置后为4,2,3,1
	a.assign({ 1,2,3,4,5,6 });
	reverse(a.begin(), a.end());
	printVector(a);

	//把a中的从a.begin()（包括它）到a.end()（不包括它）的元素复制到b中，从b.begin()+1的位置（包括它）开始复制，覆盖掉原有元素
	a.assign({ 1,2,3,4,5,6 });
	b.assign({ 2,3,3,3,3,3,3 });
	copy(a.begin(), a.end(), b.begin() + 1); // 注意copy只负责将a.[begin, end)复制到目标位置，不考虑目标位置是否合法，所以如果b没有足够空间会报错；
	// copy(a.begin(), a.end(), b.begin() + 2); // 报错：因为b没有足够位置；
	printVector(b);

	//在a中的从a.begin()（包括它）到a.end()（不包括它）的元素中查找10，若存在返回其在向量中的位置
	a.assign({ 1,2,3,4,5,6 });
	auto it = find(a.begin(), a.end(), 3);
	cout << *it << endl;
	cout << it - a.begin() << endl;

	it = find(a.begin(), a.end(), 10);
	if (it == a.end()) // 重定义了==, !=等操作符
		cout << "Not Find." << endl;
	cout << bool(it == a.end()) << endl; // 必须转换为bool才能输出。。。
}
