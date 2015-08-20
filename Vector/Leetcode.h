#include <vector>
#include <map>
#include <algorithm>
#include <stdint.h>
#include <limits.h>
#include <unordered_set>
#include <iterator>
using namespace std;
using cvec_iter = decltype(declval<vector<int>>().cbegin());
class Solution
{
public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		map<int, int> vec_index;
		vector<int> result;
		for (int i = 0; i < nums.size(); i++)
		{
			vec_index[nums[i]] = i + 1;
		}
		for (int i = 0; i < nums.size(); i++)
		{
			auto temp_iter = vec_index.find(target - nums[i]);
			if (temp_iter!= vec_index.end())
			{
				auto temp_index = (*temp_iter).second;
				if (temp_index!= i + 1)
				{
					result.push_back(i + 1);
					result.push_back(temp_index);
					return result;
				}
			}
		}
	}
	vector<pair<int, int>> LineartwoSum(vector<int>& nums, int target)
	{
		vector<pair<int, int>> result;
		int begin = 0;
		int end = nums.size() - 1;
		while (begin < end)
		{
			if (nums[begin] + nums[end] ==target)
			{
				result.push_back(make_pair(begin, end));
				begin++;
				end--;
			}
			else
			{
				if (nums[begin] + nums[end] < target)
				{
					begin++;
				}
				else
				{
					end--;
				}
			}
		}
		return result;
	}
	vector<pair<int, int>> LineartwoSum(const int* begin,const int* end, int target)
	{
		vector<pair<int, int>> result;
		while (begin < end)
		{
			if (*begin + *end == target)
			{
				result.push_back(make_pair(*begin, *end));
				begin++;
				end--;
			}
			else
			{
				if (*begin + *end < target)
				{
					begin++;
				}
				else
				{
					end--;
				}
			}
		}
		return result;
	}
	
	int findnth(cvec_iter vec1_begin, cvec_iter vec1_end, cvec_iter vec2_begin, cvec_iter vec2_end, int k)
	{
		int size1 = distance(vec1_begin, vec1_end);
		int size2 = distance(vec2_begin, vec2_end);
		if (size1*size2 == 0)
		{
			if (size1 == 0)
			{
				return *(vec2_begin + k - 1);
			}
			else
			{
				return *(vec1_begin + k - 1);
			}
		}
		else
		{
			if (size2 > size1)
			{
				return findnth(vec2_begin, vec2_end, vec1_begin, vec1_end, k);
			}
			else
			{
				if (k == 1)
				{
					int begin_1 = *vec1_begin;
					int begin_2 = *vec2_begin;
					return begin_1 < begin_2 ? begin_1 : begin_2;
				}
				if (size1 + size2 == k)
				{
					int end_1=*(vec1_begin + size1 - 1);
					int end_2 = *(vec2_begin + size2 - 1);
					return end_1 > end_2 ? end_1 : end_2;
				}
				else
				{
					int middle = *(vec1_begin + (size1 - 1) / 2);
					int vec1_mid_len = (size1 + 1) / 2;
					auto vec2_middle = upper_bound(vec2_begin, vec2_end, middle);
					int vec2_mid_len = vec2_middle - vec2_begin;
					if (vec2_mid_len + vec1_mid_len == k)
					{
						return middle;
					}
					else
					{
						if (vec1_mid_len + vec2_mid_len < k)
						{
							return findnth(vec1_begin + vec1_mid_len, vec1_end, vec2_middle, vec2_end, k - vec1_mid_len - vec2_mid_len);
						}
						else
						{
							return findnth(vec1_begin, vec1_begin + vec1_mid_len, vec2_begin, vec2_middle, k);
						}
					}
				}
			}
		}
	}
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		int size1 = nums1.size();
		int size2 = nums2.size();
		if ((size1 + size2) % 2 == 1)
		{
			return findnth(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), (size1 + size2 + 1) / 2);
		}
		else
		{
			double left = findnth(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), (size1 + size2 + 1) / 2);
			double right = findnth(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), (size1 + size2 + 3) / 2);
			return (left + right) / 2;

		}
		
	}
	int reverse(int x)
	{
		bool neg;
		int64_t temp;
		int64_t result;
		if (x < 0)
		{
			neg = true;
			temp = -x;
		}
		else
		{
			neg = false;
			temp = x;
		}
		vector<int> rev;
		while (temp > 0)
		{
			rev.push_back(temp % 10);
			temp /= 10;
		}
		result = 0;
		for (int i = 0; i < rev.size(); i++)
		{
			result = result * 10 + rev[i];
		}
		if (neg)
		{
			result *= -1;
		}
		if (result<INT_MIN || result>INT_MAX)
		{
			return 0;
		}
		else
		{
			return result;
		}
	}
	bool isPalindrome(int x)
	{
		if (x < 0)
		{
			return false;
		}
		if (x < 10)
		{
			return true;
		}
		int left;
		int right;
		int number_of_bits = log10(x);
		if (number_of_bits % 2 == 0)
		{
			int carry = 1;
			for (int i = 0; i < number_of_bits / 2; i++)
			{
				carry *= 10;
			}
			left = x / (carry * 10);
			right = x % (carry);
			
		}
		else
		{
			int carry = 1;
			for (int i = 0; i < number_of_bits / 2+1; i++)
			{
				carry *= 10;
			}
			left = x / (carry );
			right = x % (carry);
		}
		if (reverse(left) == right)
		{
			return true;
		}
	}
	int maxArea(vector<int>& height)
	{
		vector<pair<int,int>> max_height;
		if (height.size() < 2)
		{
			return 0;
		}
		int current_max = height[0];
		int max_area = 0;
		max_height.push_back(make_pair(height[0],0));
		for (int i = 1; i < height.size(); i++)
		{
			if (height[i]>current_max)
			{
				max_height.push_back(make_pair(height[i], i));
				current_max = height[i];
			}
			else
			{
				for (int j = 0; j < max_height.size(); j++)
				{
					int temp = std::min(max_height[j].first , height[i])*(i - max_height[j].second);
					if (temp > max_area)
					{
						max_area = temp;
					}
				}
			}
		}
		int size = max_height.size();
		if (size >= 2)
		{
			for (int i = 0; i <size - 1; i++)
			{
				int temp = max_height[i].first*(max_height[size - 1].second - max_height[i].second);
				if (temp > max_area)
				{
					max_area = temp;
				}
			}
		}
		return max_area;
		
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
		std::unique_copy(nums.begin(), nums.end(), std::back_inserter(new_nums));
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
	int threeSumClosest(vector<int>& nums, int target)
	{
		int result;
		if (nums.size() < 3)
		{
			return 0;
		}
		sort(nums.begin(), nums.end());
		vector<int> double_kill;
		vector<int> triple_kill;
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
					if (counter >= 3)
					{
						triple_kill.push_back(prev);
					}

					double_kill.push_back(prev);

				}
				prev = nums[i];
				counter = 1;
			}
		}
		if (counter >= 2)
		{
			if (counter >= 3)
			{
				triple_kill.push_back(prev);
			}

			double_kill.push_back(prev);

		}
		vector<int> new_nums;

		std::unique_copy(nums.begin(), nums.end(), std::back_inserter(new_nums));
		int new_size = new_nums.size();
		result = nums[0] + nums[1] + nums[2];
		for (int i = 0; i < new_size - 2; i++)
		{

			for (int j = i + 1; j < new_size - 1; j++)
			{
				auto lower = lower_bound(&new_nums[j], &new_nums[0] + new_size, target - new_nums[i] - new_nums[j]);
				int a = lower - &new_nums[0] - 1;
				int b = lower - &new_nums[0];
				int k = lower - &new_nums[0] - 1 > j + 1 ? lower - &new_nums[0] - 1 : j + 1;
				for (; k < new_nums.size() && k<lower - &new_nums[0] + 2; k++)
				{

					int current_result = new_nums[i] + new_nums[j] + new_nums[k];
					if (abs(current_result - target) < abs(result - target))
					{
						result = current_result;
					}
					if (result == target)
					{
						return result;
					}
				}
			}

		}
		for (int i = 0; i < double_kill.size(); i++)
		{

			int left = target - 2 * double_kill[i];
			auto lower = lower_bound(new_nums.begin(), new_nums.end(), left);
			if (lower != new_nums.end() && *lower != double_kill[i])
			{
				int current_result = 2 * double_kill[i] + *lower;
				if (abs(current_result - target) < abs(result - target))
				{
					result = current_result;
				}
			}
			if (lower != new_nums.begin() && *(--lower) != double_kill[i])
			{
				int current_result = 2 * double_kill[i] + *lower;
				if (abs(current_result - target) < abs(result - target))
				{
					result = current_result;
				}
			}
			if (result == target)
			{
				return result;
			}
		}
		for (auto i : triple_kill)
		{
			int current_result = 3 * i;
			if (abs(current_result - target) < abs(result - target))
			{
				result = current_result;
			}
		}
		return result;
	}

	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>> result;
		if (nums.size() < 4)
		{
			return result;
		}
		sort(nums.begin(), nums.end());
		vector<int> double_kill;
		vector<int> trible_kill;
		vector<int> monster_kill;
		unordered_set<int> hash_set;
		unordered_set<int> double_set;
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
				switch (counter)
				{
				case 1:
					break;
				case 2:
					double_set.insert(prev);
					double_kill.push_back(prev);
					break;
				case 3:
					double_set.insert(prev);
					double_kill.push_back(prev);
					trible_kill.push_back(prev);
					break;
				default:
					double_set.insert(prev);
					double_kill.push_back(prev);
					trible_kill.push_back(prev);
					monster_kill.push_back(prev);
					break;
				}
				hash_set.insert(prev);
				prev = nums[i];
				counter = 1;
			}
		}
		switch (counter)
		{
		case 1:
			break;
		case 2:
			double_set.insert(prev);
			double_kill.push_back(prev);
			break;
		case 3:
			double_set.insert(prev);
			double_kill.push_back(prev);
			trible_kill.push_back(prev);
			break;
		default:
			double_set.insert(prev);
			double_kill.push_back(prev);
			trible_kill.push_back(prev);
			monster_kill.push_back(prev);
			break;
		}
		hash_set.insert(prev);
		vector<int> new_nums;
		std::unique_copy(nums.begin(), nums.end(), std::back_inserter(new_nums));
		int new_size = new_nums.size();
		for (int i = 0; i < new_size - 3 && new_nums[i] <= target / 4; i++)
		{
			for (int j = i + 1; j < new_size - 2 && new_nums[i] + new_nums[j] <= target / 2; j++)
			{
				auto partial_result = LineartwoSum(&new_nums[j + 1], &new_nums[new_size - 1], target - new_nums[i] - new_nums[j]);
				for (auto k : partial_result)
				{
					vector<int> temp;
					temp.push_back(new_nums[i]);
					temp.push_back(new_nums[j]);
					temp.push_back(k.first);
					temp.push_back(k.second);
					result.push_back(temp);
				}
			}
		}
		for (int i = 0; i < double_kill.size(); i++)
		{
			int left = target - 2 * double_kill[i];
			if (left % 2 == 0 && double_set.find(left / 2) != double_set.end() && left / 2 > double_kill[i])
			{
				vector<int> temp;
				temp.push_back(double_kill[i]);
				temp.push_back(double_kill[i]);
				temp.push_back(left / 2);
				temp.push_back(left / 2);
				result.push_back(temp);
			}
			auto partial_result = LineartwoSum(&new_nums[0], &new_nums[new_size - 1], left);
			for (auto j : partial_result)
			{
				vector<int> temp;
				if (double_kill[i] < j.first)
				{

					temp.push_back(double_kill[i]);
					temp.push_back(double_kill[i]);
					temp.push_back(j.first);
					temp.push_back(j.second);
					result.push_back(temp);
				}
				if (j.first < double_kill[i] && double_kill[i] < j.second)
				{


					temp.push_back(j.first);
					temp.push_back(double_kill[i]);
					temp.push_back(double_kill[i]);
					temp.push_back(j.second);
					result.push_back(temp);
				}
				if (double_kill[i] > j.second)
				{


					temp.push_back(j.first);

					temp.push_back(j.second);
					temp.push_back(double_kill[i]);
					temp.push_back(double_kill[i]);
					result.push_back(temp);
				}

			}
		}
		for (int i = 0; i < trible_kill.size(); i++)
		{
			if (hash_set.find(target - 3 * trible_kill[i]) != hash_set.end() && 4 * trible_kill[i] != target)
			{
				vector<int> temp;
				if (4 * trible_kill[i] < target)
				{

					temp.push_back(trible_kill[i]);
					temp.push_back(trible_kill[i]);
					temp.push_back(trible_kill[i]);
					temp.push_back(target - 3 * trible_kill[i]);
				}
				else
				{
					temp.push_back(target - 3 * trible_kill[i]);
					temp.push_back(trible_kill[i]);
					temp.push_back(trible_kill[i]);
					temp.push_back(trible_kill[i]);

				}
				result.push_back(temp);
			}
		}
		for (int i = 0; i < monster_kill.size(); i++)
		{
			if (4 * monster_kill[i] == target)
			{
				vector<int> temp;
				temp.push_back(monster_kill[i]);
				temp.push_back(monster_kill[i]);
				temp.push_back(monster_kill[i]);
				temp.push_back(monster_kill[i]);
				result.push_back(temp);
			}
		}
		return result;
	}
	vector<string> generateParenthesis(int n)
	{
		vector<vector<string>> all_parenthese;
		all_parenthese.push_back(vector<string>());
		all_parenthese[0].push_back("");
		all_parenthese.push_back(vector<string>());
		all_parenthese[1].push_back("()");
		for (int i = 2; i < n + 1; i++)
		{
			all_parenthese.push_back(vector<string>());
			for (int j = 1; j <= i; j++)
			{
				auto left = all_parenthese[j - 1];
				auto right = all_parenthese[i - j];
				for (auto s : left)
				{
					for (auto m : right)
					{
						all_parenthese[i].push_back('(' + s + ')' + m);
					}
				}
			}
		}
		return all_parenthese[n];
	}
	int removeDuplicates(vector<int>& nums)
	{
		/*auto new_iter = unique(nums.begin(), nums.end());
		return distance(nums.begin(), new_iter);*/
		if (nums.size() == 0)
		{
			return 0;
		}
		int length = 1;
		int prev = nums[0];
		
		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] != prev)
			{
				nums[length++] = nums[i];
				prev = nums[i];
			}
		}
		return length;
	}
	int removeElement(vector<int>& nums, int val)
	{
		int length = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != val)
			{
				nums[length++] = nums[i];
			}
		}
		return length;
	}
	int firstMissingPositive(vector<int>& nums)
	{
		int i = 0, j;
		int n = nums.size();
		while (i < n)
		{
			if (nums[i] != i + 1 && nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
			{
				swap(nums[i], nums[nums[i] - 1]);
			}

			else
			{
				i++;
			}
		}

		for (j = 0; j < n; j++)
		{
			if (nums[j] != j + 1)
			{
				return j + 1;
			}

		}

		return n + 1;
	}
	int trap(vector<int>& height)
	{
		vector<int> right_height(height.size(), 0);
		int current_height = 0;
		for (int i = height.size() - 1; i >= 0; i--)
		{
			
			right_height[i] = current_height;
			if (height[i]>current_height)
			{
				current_height = height[i];
			}
			
		}
		current_height = 0;
		int total = 0;
		for (int i = 0; i < height.size(); i++)
		{
			int min = std::min(current_height, right_height[i]);
			if (min>height[i])
			{
				total += min - height[i];

			}
			if (height[i] > current_height)
			{
				current_height = height[i];
			}

		}
		return total;
	}
	int longestValidParentheses(string s)
	{
		int size = s.length();
		if (size < 2)
		{
			return 0;
		}
		int max = 0;
		vector<int> result(size, 0);
		for (int i = 1; i < size; i++)
		{
			if (s[i] == ')')
			{
				if (s[i - 1] == ')')
				{
					int left = i - result[i - 1]-1;
					if (left >= 0 && s[left] == '(')
					{
						result[i] = result[i - 1] + 2;
						if (left > 1)
						{
							result[i] += result[left - 1];
						}
						max = max > result[i] ? max : result[i];
					}
					else
					{
						result[i] = 0;
					}
				}
				else
				{
					result[i] = 2;
					if (i > 2 && s[i - 2] == ')')
					{
						result[i] += result[i - 2];
					}
					max = max > result[i] ?  max : result[i];
				}
			}
		}
		return max;
	}
	vector<vector<int>> help_combSum(int* begin, int * end, int target)
	{
		vector<vector<int>> result;
		if (begin == end)
		{
			return result;
		}
		if (*begin > target)
		{
			return result;
		}
		for (int i = 0; i <= target / (*begin); i++)
		{
			int new_target = target - i*(*begin);
			vector<int> temp;
			for (int k = 0; k < i; k++)
			{
				temp.push_back(*begin);
			}
			if (new_target == 0)
			{
				result.push_back(temp);
			}
			else
			{
				auto temp_result = help_combSum(begin + 1, end,new_target );
				if (temp_result.size() != 0)
				{
					for (auto s : temp_result)
					{
						vector<int> new_temp = temp;
						copy(s.begin(), s.end(), back_inserter(new_temp));
						result.push_back(new_temp);
					}
					
				}
			}
			
		}
		return result;
	}
	
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		sort(candidates.begin(), candidates.end());
		int length= distance(candidates.begin(), unique(candidates.begin(), candidates.end()));
		return help_combSum(&candidates[0], &candidates[length], target);

	}
	map<int, int> dup_counter;
	vector<vector<int>> help_combSum2(int* begin, int * end, int target)
	{
		vector<vector<int>> result;
		if (begin == end)
		{
			return result;
		}
		if (*begin > target)
		{
			return result;
		}
		int max_counter = std::min(target / (*begin), dup_counter[*begin]);
		for (int i = 0; i <=max_counter; i++)
		{
			int new_target = target - i*(*begin);
			vector<int> temp;
			for (int k = 0; k < i; k++)
			{
				temp.push_back(*begin);
			}
			if (new_target == 0)
			{
				result.push_back(temp);
			}
			else
			{
				auto temp_result = help_combSum(begin + 1, end, new_target);
				if (temp_result.size() != 0)
				{
					for (auto s : temp_result)
					{
						vector<int> new_temp = temp;
						copy(s.begin(), s.end(), back_inserter(new_temp));
						result.push_back(new_temp);
					}

				}
			}

		}
		return result;
	}
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	{
		sort(candidates.begin(), candidates.end());
		int prev = candidates[0];
		int counter = 1;
		for (int i = 1; i < candidates.size(); i++)
		{
			if (candidates[i] == prev)
			{
				counter++;
			}
			else
			{
				dup_counter[prev]=counter;
				prev = candidates[i];
				counter = 1;
			}
		}
		dup_counter[prev] = counter;
		int length = distance(candidates.begin(), unique(candidates.begin(), candidates.end()));
		return help_combSum2(&candidates[0], &candidates[length], target);
	}
	int maxSubArray(vector<int>& nums)
	{
		int max = nums[0];
		int current_sum = nums[0];
		int size = nums.size();
		for (int i = 1; i < size; i++)
		{

			if (current_sum <0)
			{
				current_sum = 0;
			}
			current_sum += nums[i];
			if (current_sum > max)
			{
				max = current_sum;
			}

		}
		return max;

	}
	bool canJump(vector<int>& nums)
	{
		int max_end = 0;
		int current = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (i > max_end)
			{
				return false;
			}
			else
			{
				int temp = nums[i] + i;
				max_end = std::max(temp, max_end);
				if (max_end >= nums.size() - 1)
				{
					return true;
				}
			}
		}
	}
	int removeDuplicates(vector<int>& nums)
	{
		if (nums.size() == 0)
		{
			return 0;
		}
		int length = 1;
		int prev = nums[0];

		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] != prev)
			{
				nums[length++] = nums[i];
				prev = nums[i];
			}
		}
		return length;
	}
	int removeDuplicates2(vector<int>& nums)
	{
		if (nums.size() == 0)
		{
			return 0;
		}
		int length = 1;
		int counter = 1;
		int prev = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] != prev)
			{
				nums[length++] = nums[i];
				prev = nums[i];
				counter=1;
			}
			else
			{
				if (counter == 1)
				{
					nums[length++] = nums[i];
				}
				counter++;
			}
		}
		return length;
	}
	int climbStairs(int n)
	{
		vector<int> ways(n, 0);
		ways[0] = 1;
		ways[1] = 2;
		for (int i = 2; i < n; i++)
		{
			ways[i] = ways[i - 1] + ways[i - 2];
		}
		return ways[n - 1];
	}
	int largestRectangleArea(vector<int>& height)
	{

		vector<pair<int, int>> increasing_h;
		int size = 1;
		int max = 0;
		increasing_h.push_back(make_pair(-1, -1));
		height.push_back(0);
		for (int i = 0; i < height.size(); i++)
		{
			while ( increasing_h[size - 1].first >= height[i])
			{
				int current_result = increasing_h[size - 1].first  * (i - increasing_h[size - 2].second - 1);
				max = std::max(max, current_result);
				increasing_h.pop_back();
				size--;
			}
			increasing_h.push_back(make_pair(height[i], i));
			size++;


		}
		return max;
	}
	int maximalRectangle(vector<vector<char>>& matrix)
	{
		vector<int> temp(matrix[0].size(), 0);
		int max = 0;
		for (const auto& i : matrix)
		{
			for (int j = 0; j < i.size(); j++)
			{
				if (i[j] == '1')
				{
					temp[j]++;
				}
				else
				{
					temp[j] = 0;
				}
			}
			int temp_area = largestRectangleArea(temp);
			max = std::max(temp_area, max);
		}
		return max;
	}
	int search(vector<int>& nums, int target)
	{
		if (nums.size() == 0)
		{
			return -1;
		}
		int begin =0;
		int end = nums.size();
		while (begin != end)
		{
			int middle = (begin + end ) / 2;
			if (nums[middle] == target)
			{
				return middle;
			}
			if (nums[middle] < nums[begin])
			{
				if (target > nums[middle]&&target<nums[begin])
				{
					begin = middle + 1;
					
				}
				else
				{
					end = middle;
				}
			}
			else
			{
				if (target >= nums[begin]&& target<nums[middle])
				{
					end = middle;
				}
				else
				{
					begin = middle + 1;
				}
			}
		}
		return -1;
	}
	void permute_dfs(vector<vector<int>>& result, vector<int>& input, int k)
	{
		if (k == input.size())
		{
			result.push_back(input);
		}
		else
		{
			for (int i = k; i < input.size(); i++)
			{
				swap(input[k], input[i]);
				permute_dfs(result, input, k + 1);
				swap(input[k], input[i]);
			}
		}
	}
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<vector<int>> result;
		permute_dfs(result, nums, 0);
		return result;
	}

	vector<vector<int>> permuteUnique(vector<int>& nums)
	{

	}
	using vec_iter = decltype(declval<vector<int>>().begin());
	bool my_next_permu(vector<int>& hehe)
	{
		if (hehe.size()<2)
		{
			return false;
		}
		int size = hehe.size();
		int cursor = size - 1;
		while (cursor > 0 && hehe[cursor - 1] >= hehe[cursor])
		{
			cursor--;
		}
		if (cursor == 0)
		{
			return false;
		}
		else
		{
			std::reverse(&hehe[cursor], &hehe[size - 1] + 1);
			auto upper = upper_bound(&hehe[cursor], &hehe[size - 1] + 1, hehe[cursor - 1]);
			int temp = *upper;
			*upper = hehe[cursor - 1];
			hehe[cursor - 1] = temp;
			return true;
		}
	}


	vector<vector<int>> subsets(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		int size = nums.size();
		vector<vector<int>> result;
		result.push_back(vector<int>());
		uint32_t bit_mask = (1 << size) - 1;
		while (bit_mask > 0)
		{
			int i = 0;
			vector<int> temp_set;
			uint32_t temp = bit_mask;
			while (temp != 0)
			{
				if (temp&(1 << i))
				{
					temp_set.push_back(nums[i]);
					temp = temp - (1 << i);
				}
				i++;
			}
			result.push_back(temp_set);
			bit_mask--;
		}
		return result;
	}
	int break_point(int* begin,int* end)
	{
		if (end - begin < 2)
		{
			return 0;
		}

		if (*(end - 1) > *begin)
		{
			return 0;
		}
		int* middle = begin + (end - begin) / 2;
		if (*middle == *begin)
		{
			return break_point(begin, middle + 1) | break_point(middle, end);
		}
		else
		{
			if (*middle > *begin)
			{
				return break_point(middle, end);
			}
			else
			{
				return break_point(begin, middle + 1);
			}
		}
	}
};
