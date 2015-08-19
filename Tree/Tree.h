#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
 };

class Solution
{
public:
	vector<Interval> merge(vector<Interval>& intervals)
	{
		map<int, int> all_intervals;
		for (auto i : intervals)
		{
			int start = i.start;
			int end = i.end;
			auto delete_begin = all_intervals.lower_bound(start);
			auto delete_end = all_intervals.upper_bound(end);
			if (delete_begin != all_intervals.begin())
			{
				delete_begin--;
				if (delete_begin->second >= start)
				{
					start = delete_begin->first;
				}
				else
				{
					delete_begin++;
				}
			}
			if (delete_end != all_intervals.begin())
			{
				delete_end--;
				if (delete_end->second > end)
				{
					end = delete_end->second;
				}
				delete_end++;
			}
			all_intervals.erase(delete_begin, delete_end);
			all_intervals[start] = end;
		}
		vector<Interval> result;
		for (auto i : all_intervals)
		{
			result.push_back(Interval(i.first, i.second));
		}
		return result;
	}
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
	{
		
		map<int, int> all_intervals;
		for (auto i : intervals)
		{
			all_intervals[i.start] = i.end;
		}
		
		int start = newInterval.start;
		int end = newInterval.end;
			auto delete_begin = all_intervals.lower_bound(start);
			auto delete_end = all_intervals.upper_bound(end);
			if (delete_begin != all_intervals.begin())
			{
				delete_begin--;
				if (delete_begin->second >= start)
				{
					start = delete_begin->first;
				}
				else
				{
					delete_begin++;
				}
			}
			if (delete_end != all_intervals.begin())
			{
				delete_end--;
				if (delete_end->second > end)
				{
					end = delete_end->second;
				}
				delete_end++;
			}
			all_intervals.erase(delete_begin, delete_end);
			all_intervals[start] = end;
		vector<Interval> result;
		for (auto i : all_intervals)
		{
			result.push_back(Interval(i.first, i.second));
		}
		return result;
	}
};