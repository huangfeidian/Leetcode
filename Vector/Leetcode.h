#include <vector>
#include <map>
#include <algorithm>
#include <stdint.h>
#include <limits.h>
using namespace std;
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
	using cvec_iter = decltype(declval<vector<int>>().cbegin());
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
};