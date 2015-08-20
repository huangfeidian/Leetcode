#include <vector>
#include <unordered_set>
#include <stdint.h>
#include <stack>
#include <algorithm>
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
void rotate(vector<vector<int>>& matrix)
{
	if (matrix.size() < 2)
	{
		return;
	}
	float middle = matrix.size() - 1;
	for (int i = 0; i <= middle/2; i++)
	{
		for (int j = 0; j < middle/2; j++)
		{
			int row_1, row_2, row_3, row_4;
			int col_1, col_2, col_3, col_4;
			row_1 = i;
			col_1 = j;
			col_2 = middle - row_1;
			row_2 = col_1;
			row_3 =  middle - row_1;
			col_3 =  middle - col_1;
			row_4 =  middle - row_2;
			col_4 = middle - col_2;
			int temp_val = matrix[row_4][col_4];
			matrix[row_4][col_4] = matrix[row_3][col_3];
			matrix[row_3][col_3] = matrix[row_2][col_2];
			matrix[row_2][col_2] = matrix[row_1][col_1];
			matrix[row_1][col_1] = temp_val;
		}
	}
}
vector<int> spiralOrder(vector<vector<int>>& matrix)
{
	int turn = 0;
	int sum = 0;
	int i = 0;
	int j = 0;
	vector<int> result;
	int m = matrix.size();
	if (m == 0)
	{
		return result;
	}
	int n = matrix[0].size();

	while (1)
	{
		result.push_back(matrix[i][j]);
		matrix[i][j] = INT_MAX;
		sum++;
		if (sum == m*n)
		{
			return result;
		}
		switch (turn)
		{
		case 0:
			if (j == n - 1 || matrix[i][j + 1] == INT_MAX)
			{
				i++;
				turn = 1;
			}
			else
			{
				j++;
			}
			break;
		case 1:
			if (i == m - 1 || matrix[i + 1][j] == INT_MAX)
			{
				j--;
				turn = 2;
			}
			else
			{
				i++;
			}
			break;
		case 2:
			if (j == 0 || matrix[i][j - 1] == INT_MAX)
			{
				i--;
				turn = 3;
			}
			else
			{
				j--;
			}
			break;
		case 3:
			if (i == 0 || matrix[i - 1][j] == INT_MAX)
			{
				j++;
				turn = 0;
			}
			else
			{
				i--;
			}
			break;

		}
	}
}
vector<vector<int>> generateMatrix(int n)
{
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	int turn = 0;
	int sum = 1;
	int i = 0;
	int j = 0;

	if (n == 0)
	{
		return matrix;
	}
	

	while (1)
	{
		matrix[i][j]=sum;
		sum++;
		if (sum == n*n+1)
		{
			return matrix;
		}
		switch (turn)
		{
		case 0:
			if (j == n - 1 || matrix[i][j + 1] >0)
			{
				i++;
				turn = 1;
			}
			else
			{
				j++;
			}
			break;
		case 1:
			if (i == n - 1 || matrix[i + 1][j] >0)
			{
				j--;
				turn = 2;
			}
			else
			{
				i++;
			}
			break;
		case 2:
			if (j == 0 || matrix[i][j - 1] >0)
			{
				i--;
				turn = 3;
			}
			else
			{
				j--;
			}
			break;
		case 3:
			if (i == 0 || matrix[i - 1][j] >0)
			{
				j++;
				turn = 0;
			}
			else
			{
				i--;
			}
			break;

		}
	}
}
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
	int m = matrix.size();
	if (m == 0)
	{
		return false;
	}
	int n = matrix[0].size();
	int lower_begin, lower_end;
	lower_begin = 0;
	lower_end = m ;
	while (lower_begin < lower_end)
	{
		int lower_middle = (lower_begin + lower_end) / 2;
		if (matrix[lower_begin][0] == target)
		{
			lower_begin = lower_end=lower_middle;
		}
		else
		{
			if (matrix[lower_begin][0] > target)
			{
				lower_end = lower_middle;
			}
			else
			{
				lower_begin = lower_middle + 1;
			}
		}
	}
	if (lower_begin == 0 )
	{
		return matrix[0][0] == target;
		
	}
	if (lower_begin == m)
	{
		return binary_search(matrix[m - 1].begin(), matrix[m - 1].end(), target);
	}
	else
	{
		return  matrix[lower_begin ][0] == target || (binary_search(matrix[lower_begin - 1].begin(), matrix[lower_begin - 1].end(), target));
	}
}
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
	int m = obstacleGrid.size();
	if (m == 0)
	{
		return 0;
	}
	int n = obstacleGrid[0].size();
	vector<vector<int> > f(m, vector<int>(n));
	int prev = 1;
	for (int i = 0; i < n; i++)
	{
		f[0][i] = (1 - obstacleGrid[0][i])*prev;
		prev = f[0][i];
	}
	prev = 1;
	for (int i = 0; i < m; i++)
	{
		f[i][0] = (1 - obstacleGrid[i][0])*prev;
		prev = f[i][0];
	}
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{

			f[i][j] = (1 - obstacleGrid[i][j])*(f[i - 1][j] + f[i][j - 1]);

		}
	}

	return f[m - 1][n - 1];

}
int minPathSum(vector<vector<int>>& grid)
{
	int m = grid.size();
	int n = grid[0].size();
	int prev = 0;
	vector<vector<int> > f(m, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		f[0][i] = grid[0][i]+prev;
		prev = f[0][i];
	}
	prev = 0;
	for (int i = 0; i < m; i++)
	{
		f[i][0] = grid[i][0]+prev;
		prev = f[i][0];
	}
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{

			f[i][j] = std::min(f[i-1][j],f[i][j-1])+grid[i][j];

		}
	}

	return f[m - 1][n - 1];

}
struct node_index
{
	char value;
	int i;
	int j;
	int k;
};
bool board_dfs(vector < vector<int>>& used, vector<vector<node_index>>& all_nodes, string& s, int index, int k)
{
	if (index == s.length())
	{
		return true;
	}
	vector<node_index>& current_nodes = all_nodes[k];
	for (auto i : current_nodes)
	{
		if (i.value == s[index] && used[i.i][i.j]!=1)
		{
			used[i.i][i.j] = 1;
			if (board_dfs(used, all_nodes, s, index + 1, i.k))
			{
				return true;
			}
			else
			{
				used[i.i][i.j] = 0;
			}
		}
	}
}
bool exist(vector<vector<char>>& board, string word)
{
	int m = board.size();
	if (m == 0)
	{
		return false;
	}
	if (word.length() == 0)
	{
		return true;
	}
	int n = board[0].size();
	int char_set[128] = { 0 };
	for (auto i : word)
	{
		char_set[i] = 1;
	}
	vector<vector<node_index>> all_nodes(m*n, vector<node_index>());
	vector<vector<int>> used(m, vector<int>(n, 0));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int left = j- 1;
			int right = j + 1;
			int up = i - 1;
			int down = i + 1;
			if (left >= 0 && char_set[board[i][left]]==1)
			{
				node_index current{ board[i][left], i, left ,i*n+left};
				all_nodes[i*n + j].push_back(current);
			}
			if (right < n&&char_set[board[i][right]] == 1)
			{
				node_index current{ board[i][right], i, right,i*n+right };
				all_nodes[i*n + j].push_back(current);
			}
			if (up >= 0 && char_set[board[up][j]] == 1)
			{
				node_index current{ board[up][j], up, j,up*n+j };
				all_nodes[i*n + j].push_back(current);
			}
			if (down< m&&char_set[board[down][j]] == 1)
			{
				node_index current{ board[down][j], down, j,down*n+j };
				all_nodes[i*n + j].push_back(current);
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j] == word[0])
			{
				used[i][j] = 1;
				if (board_dfs(used, all_nodes, word, 1, i*n+j))
				{
					return true;
				}
				else
				{
					used[i][j] = 0;
				}
			}
		}
	}
	return false;
}