#include<iostream>
#include<vector>
using namespace std;


//sum1 为前i-1个最大和
//sum2 为加上i号位置元素的最大和sum2 = sum1+nums[i];if(sum2<0) sum2 = 0;
//最后将sum1的值赋值给sum2
int main()
{
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}
	int sum1 = 0;
	int sum2 = 0;
	int result = nums[0];
	for (int i = 0; i < n; ++i)
	{
		if (sum1 > 0)
			sum2 = sum1 + nums[i];
		else
			sum2 = nums[i];
		if (result < sum2)
			result = sum2;
		if (sum2 < 0)
			sum2 = 0;
		sum1 = sum2;
	}
	cout << result;
	system("pause");
	return 0;
}