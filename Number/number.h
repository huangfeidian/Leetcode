#include <vector>
#include <unordered_set>
#include <map>
#include <stdint.h>
#include <string>
using namespace std;
int divide(int dividend, int divisor)
{
	int64_t new_dividend, new_divisor;
	bool is_neg = false;
	new_dividend = dividend;
	new_divisor = divisor;
	if (new_dividend < 0)
	{
		is_neg = !is_neg;
		new_dividend *= -1;
	}
	if (new_divisor < 0)
	{
		is_neg = !is_neg;
		new_divisor *= -1;
	}

	int64_t carry = 1;
	int64_t temp = new_divisor;
	while (temp < new_dividend)
	{
		carry <<= 1;
		temp <<= 1;
	}
	int64_t remain = new_dividend;
	int64_t result = 0;
	while (remain >= new_divisor)
	{
		if (remain < temp)
		{
			temp >>= 1;
			carry >>= 1;
		}
		else
		{
			remain -= temp;
			result += carry;
			temp >>= 1;
			carry >>= 1;
		}
	}
	if (is_neg)
	{
		result *= -1;
	}
	if (result > INT_MAX || result < INT_MIN)
	{
		return INT_MAX;
	}
	else
	{
		return result;
	}
}
void int_to_vec(int num, vector<int>& input_vec)
{
	while (num > 0)
	{
		input_vec.push_back(num % 10);
		num /= 10;
	}
	reverse(input_vec.begin(), input_vec.end());
}
string countAndSay(int n)
{
	vector<int> pre,after,countvec;
	pre.push_back('1');
	char temp;
	int count, size;;
	for (int j = 1; j< n; j++)
	{
		temp = pre[0];
		count = 1;
		size = pre.size();
		int i;
		for (i = 1; i < size; i++)
		{
			if (pre[i] == temp)
			{
				count++;
			}
			else
			{
				int_to_vec(count,countvec);
				copy(countvec.begin(), countvec.end(), back_inserter(after));
				after.push_back(temp);
				countvec.clear();
				temp = pre[i];
				count = 1;
			}
		}
		int_to_vec(count, countvec);
		copy(countvec.begin(), countvec.end(), back_inserter(after));
		after.push_back(temp);
		countvec.clear();
		pre.swap(after);
		after.clear();
	}
	string result;
	result.reserve(pre.size());
	for (auto s : pre)
	{
		result.push_back(s + '0');
	}
	return result;
}
string multiply(string num1, string num2)
{
	uint64_t num_1, num_2;
	num_1=stoull(num1);
	num_2=stoull(num2);
	uint64_t upper, lower;
	if (num_1 == 0 || num_2 == 0)
	{
		upper = lower = 0;
	}
}
int jump(vector<int>& nums)
{
	vector<int> steps(nums.size(), 0);
	for (int i = 0; i < nums.size()-1; i++)
	{
		for (int k = i + 1; k <= i + nums[i]&&k<nums.size(); k++)
		{
			steps[k] = steps[k] < steps[i] + 1 ? steps[k] : steps[i] + 1;
		}
	}
	return steps[nums.size() - 1];

}