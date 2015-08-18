#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;
int lengthOfLongestSubstring(string s)
{
	map<char, int> char_index;
	int begin_of_substr=0;
	int current_max=0;
	for (int i = 0; i < s.length(); i++)
	{
		if (char_index.find(s[i]) == char_index.end())
		{
			char_index[s[i]] = i;
		}
		else
		{
			int before_index = char_index[s[i]];
			int current_len = i - begin_of_substr;
			for (int j = begin_of_substr; j<before_index; j++)
			{
				char_index.erase(s[j]);
			}
			begin_of_substr = before_index + 1;
			
			current_max = current_max>current_len ? current_max : current_len;
			char_index[s[i]] = i;
		}
	}
	int tail_len = s.length() - begin_of_substr;
	return current_max>tail_len?current_max:tail_len;
}
string manacher(string s)
{
	string temp;
	temp.reserve(2 * (s.length() + 1));
	for (int i = 0; i < s.length(); i++)
	{
		temp.push_back('#');
		temp.push_back(s[i]);
	}
	temp.push_back('#');
	temp.push_back('\0');
	vector<int> result(2*s.length()+1, 0);
	int right_bar = 0;
	int center=0;
	int max_len = 0;
	int max_center = 0;
	for (int i = 0; i < temp.length(); i++)
	{
		if (i < right_bar)
		{
			int left = 2 * center - i;
			int left_len = result[left];
			int right_len = right_bar - i;
			if (left_len != right_len)
			{
				result[i] = left_len < right_len ? left_len : right_len;
			}
			else
			{
				int j = right_len;
				for (; i+j < temp.length() && i >= j; j++)
				{
					if (temp[j + i] != temp[i - j])
					{
						break;
					}
				}

				center = i;
				right_bar = i+j - 1;
				result[i] = right_bar - center;
				if (right_bar - center > max_len)
				{
					max_len = right_bar - center;
					max_center = i;
				}
			}
		}
		else
		{
			int j = 0;
			for (; i+j < temp.length() && i >= j; j++)
			{
				if (temp[j + i] != temp[i - j])
				{
					break;
				}
			}
			center = i;
			right_bar = i+j - 1;
			if (right_bar - center > max_len)
			{
				max_len = right_bar - center;
				max_center = i;
			}
			result[i] = right_bar - center;
		}
	}
	string result_string;
	result_string.reserve(max_len);
	for (int i = max_center - max_len; i <= max_center + max_len; i++)
	{
		if (temp[i] != '#')
		{
			result_string.push_back(temp[i]);
		}
	}
	return result_string;

}
void manacher(string s,  vector<int>& rad)
{
	for (int i = 1, j = 0, k; i < s.length(); i += k)
	{
		while (s[i - j - 1] == s[i + j + 1])
		{
			++j;
		}
		rad[i] = j;
		for (k = 1; k <= rad[i] && rad[i - k] != rad[i] - k; ++k)
		{ // 利用类似镜像的方法缩短了时间 
			rad[i + k] = std::min(rad[i - k], rad[i] - k);
		}
		j = std::max(j - k, 0);
	}
}

string longestPalindrome(string s)
{
	return manacher(s);
}
string convert(string s, int numRows)
{
	vector<string> result(numRows, "");
	if (numRows == 1)
	{
		return s;
	}
	for (int i = 0; i < s.length(); i++)
	{
		int temp_i = i % (2 * numRows - 2);
		if (temp_i <= numRows - 1)
		{
			result[temp_i].push_back(s[i]);
		}
		else
		{
			result[2 * numRows - 2 - temp_i].push_back(s[i]);
		}

	}
	string result_string;
	for (auto i : result)
	{
		result_string += i;
	}
	return result_string;
}
string longestCommonPrefix(vector<string>& strs)
{
	string current_prefix = strs[0];
	for (int i = 1; i < strs.size(); i++)
	{
		int j;
		for (j = 0; j < current_prefix.length() && j < strs[i].length(); j++)
		{
			if (current_prefix[j] != strs[i][j])
			{
				break;
			}
		}
		current_prefix = current_prefix.substr(0, j);
	}
	return current_prefix;
}
vector<vector<int>> threeSum(vector<int>& nums)
{

	vector<vector<int>> result;
	if (nums.size() < 3)
	{
		return result;
	}
	sort(nums.begin(), nums.end());
	vector<int> double_kill;
	bool zero_triple = false;
	unordered_set<int> hash_set;
	int prev = nums[0];
	int counter = 1;
	for (int i = 1; i < nums.size(); i++)
	{
		if (nums[i] == prev)
		{
			counter++;
		}
		else
		{
			if (counter >= 2)
			{
				if (counter >= 3 && prev == 0)
				{
					zero_triple = true;
				}

				double_kill.push_back(prev);

			}
			hash_set.insert(prev);
			prev = nums[i];
			counter = 1;
		}
	}
	if (counter >= 2)
	{
		if (counter >= 3 && prev == 0)
		{
			zero_triple = true;
		}

		double_kill.push_back(prev);

	}

	hash_set.insert(prev);
	if (zero_triple == true)
	{
		vector<int> temp;
		temp.push_back(0);
		temp.push_back(0);
		temp.push_back(0);
		result.push_back(temp);
	}
	vector<int> new_nums;
	std::unique_copy(nums.begin(), nums.end(), back_inserter(new_nums));
	for (int i = 0; i < new_nums.size(); i++)
	{
		if (nums[i] < 0)
		{
			for (int j = i + 1; j < new_nums.size(); j++)
			{
				if (new_nums[j] + new_nums[i] < 0 && (0 - new_nums[i] - new_nums[j] >new_nums[j]) && (hash_set.find(0 - new_nums[i] - new_nums[j]) != hash_set.end()))
				{
					vector<int> temp;
					temp.push_back(new_nums[i]);
					temp.push_back(new_nums[j]);
					temp.push_back(0 - new_nums[i] - new_nums[j]);
					result.push_back(temp);
				}
			}
		}
	}
	for (int i = 0; i < double_kill.size(); i++)
	{
		if (double_kill[i] != 0)
		{
			if (hash_set.find(0 - 2 * double_kill[i]) != hash_set.end())
			{
				if (double_kill[i]>0)
				{
					vector<int> temp;
					temp.push_back(0 - 2 * double_kill[i]);
					temp.push_back(double_kill[i]);
					temp.push_back(double_kill[i]);
					result.push_back(temp);
				}
				else
				{
					vector<int> temp;

					temp.push_back(double_kill[i]);
					temp.push_back(double_kill[i]);
					temp.push_back(0 - 2 * double_kill[i]);
					result.push_back(temp);
				}
			}
		}

	}
	return result;
}