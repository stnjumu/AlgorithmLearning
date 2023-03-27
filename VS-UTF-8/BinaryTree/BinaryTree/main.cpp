#include"TreeNode.h"
using namespace std;

#include"Solutions.h"
#include"BST_Solutions.h"
void solveProblem(int id) {
	if (id == 98)
	{
		Solution98 sol;
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
		TreeNode* r = vectorInt2BinaryTree({ 1, -1, 2, 3 });
		printInOrder(r);
		return 0;
	}

	vector<int> problem = vector<int>(
		{ 98 }
	);
	int id = problem.back();
	cout << "problem id = " << id << endl;
	solveProblem(*(problem.end() - 1));

	return 0;
}
