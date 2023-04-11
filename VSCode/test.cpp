#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int val = 3;
    int* pos = lower_bound(arr, arr + n, val);
    cout << "The position of the first element greater than or equal to " << val << " is: ";
    cout << (pos - arr) << endl;
    return 0;
}