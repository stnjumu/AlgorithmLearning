#include"array.h"
using namespace std;

#include"Solutions.h"
void solveProblem(int id) {
	if (id == 1)
	{
		Solution1 sol;
		cout << sol.problem << endl;
		// 以下3种初始化方法需掌握；
		//vector<int> nums({ 2,7,11,15 });
		//int target = 9;
		//// 不太对的写法：vector<int> nums = vector<int>({ 3,2,4 });
		//vector<int> nums = { 3,2,4 };
		//int target = 6;
		vector<int> nums{ 3,3 }; // ()可省略；
		int target = 6;

		vector<int> ans = sol.twoSum(nums, target);
		printVector(ans);
	}
	else if (id == 26)
	{
		vector<int> nums{ 1,1,2 };

		Solution26 sol;
		cout << sol.problem << endl;
		cout << sol.removeDuplicates(nums) << endl;
		printVector(nums);
	}
	else if (id == 35)
	{
		vector<int> nums{ 1,3,5,6 };
		int target = 7;

		Solution35 sol;
		cout << sol.problem << endl;
		cout << sol.searchInsert(nums, target);
	}
	else if (id == 136)
	{
		vector<int> nums{ 1 };

		Solution136 sol;
		cout << sol.problem << endl;
		cout << sol.singleNumber(nums) << endl;
	}
	else
	{
		cout << "Not supported id: " << id << endl;
	}

	//system("pause");
	return;
}

int main() {
	bool learning_flag = false;
	if (learning_flag)
	{
		vectorLearning();
		return 0;
	}

	vector<int> problem = vector<int>(
		{ 1,26,35,136 }
	);
	int id = problem.back();
	cout << "problem id = " << id << endl;
	solveProblem( *(problem.end()-1) );

	return 0;
}
