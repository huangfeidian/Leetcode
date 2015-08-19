#include <vector>
#include <unordered_set>
#include <stdint.h>
#include <stack>
using namespace std;
bool isValidSudoku(vector<vector<char>>& board)
{
	int row[9][9];
	int col[9][9];
	int square[9][9];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			row[i][j] = 0;
			col[i][j] = 0;
			square[i][j] = 0;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			char c = board[i][j];
			if (c >= '1'&&c <= '9')
			{
				int num = c - '1' ;
				if (row[i][num] == 1)
				{
					return false;
				}
				else
				{
					row[i][num] = 1;
				}
				if (col[j][num] == 1)
				{
					return false;
				}
				else
				{
					col[j][num] = 1;
				}
				if (square[(i/3)*3+j/3][num] == 1)
				{
					return false;
				}
				else
				{
					square[(i / 3) * 3 + j / 3][num] = 1;
				}

			}
		}
	}
	return true;
}

vector<string> temp_result;
void queen_dfs(vector<vector<string>>& result, uint32_t mask, uint32_t col, uint32_t left, uint32_t right, int k)
{
	if (col == mask)
	{
		result.push_back(temp_result);
		return;
	}
	uint32_t infeasible = left | right | col;
	uint32_t feasible = (~infeasible)&mask;
	string temp(k, '.');
	while (feasible != 0)
	{

		uint32_t right_most = feasible&((~feasible) + 1);
		int s = 0;
		while ((1 << s) != right_most)
		{
			s++;
		}
		temp[k - s - 1] = 'Q';
		temp_result.push_back(temp);
		feasible = feasible - right_most;
		queen_dfs(result, mask, col | right_most, ((left | right_most) >> 1)&mask, ((right | right_most) << 1)&mask, k);
		temp_result.pop_back();
		temp[k - s - 1] = '.';
	}

}
vector<vector<string>> solveNQueens(int n)
{
	uint32_t mask = (1 << n) - 1;
	uint32_t col, left, right;
	col = left = right = 0;
	vector<vector<string>> result;
	queen_dfs(result, mask, col, left, right, n);
	return result;
}

void count_queen_dfs(uint32_t mask, uint32_t col, uint32_t left, uint32_t right,int* total)
{
	if (col == mask)
	{
		(*total)++;
		return;
	}
	uint32_t infeasible = left | right | col;
	uint32_t feasible = (~infeasible)&mask;

	while (feasible != 0)
	{

		uint32_t right_most = feasible&((~feasible) + 1);
		int s = 0;
		while ((1 << s) != right_most)
		{
			s++;
		}


		feasible = feasible - right_most;
		count_queen_dfs(mask, col | right_most, ((left | right_most) >> 1)&mask, ((right | right_most) << 1)&mask,total);
	}

}
int totalNQueens(int n)
{
	uint32_t mask = (1 << n) - 1;
	uint32_t col, left, right;
	col = left = right = 0;
	int result = 0;
	count_queen_dfs( mask, col, left, right, &result);
	return result;
}
