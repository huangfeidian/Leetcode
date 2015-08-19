#include <vector>
using namespace std;
class Solution
{
public:
	struct basic_node
	{
		//����֮����û��left��right����Ϊ����ÿ�η���һ�е�ʱ�����ĸ���һ��ֵģ����Կ���ֱ��ͨ���Ӽ�1���㶨���ҹ�ϵ
		int down;
		int up;
		int column;
	};
	struct basic_node total_nodes[324 + 81 * 9 * 4];//324��ͷ�ڵ㣬81�����ӣ�ÿ��������9�������ÿ��������ĸ��㡣
	int avail_node_index = 324;//����ڵ�ʱ�ı��
	int node_stack[81];
	int stack_index = 0;
	struct node_heap
	{
		int cul_value;//����������е�1�ĸ���
		int position_index;//�����Ÿ�����ָʾ���е�����
	};
	struct node_heap mutual_index[324];//����Ƕ�
	int current_heap_number = 323;//����ǵ�ǰ���õĶ��еĽڵ���
	int available_column = 323;//����ǵ�ǰ��������
	int position_index[324];//��������ڶ��е�λ��
	int input[9][9];
	
	void initial(void)
	{
		for (int i = 0; i < 324; i++)
		{
			total_nodes[i].column = i;
			total_nodes[i].down = i;
			total_nodes[i].up = i;
			mutual_index[i].cul_value = 0;
			mutual_index[i].position_index = i;
			position_index[i] = i;
		}
		stack_index = 0;
		available_column = 323;
		current_heap_number = 323;
		avail_node_index = 324;
	}
	void swap_heap(int index_one, int index_two)//�����ڶ��е�����Ԫ�ص�ֵ���������������
	{
		int intermidate_one, intermidate_two;
		intermidate_one = mutual_index[index_one].cul_value;
		intermidate_two = mutual_index[index_one].position_index;
		mutual_index[index_one].cul_value = mutual_index[index_two].cul_value;
		mutual_index[index_one].position_index = mutual_index[index_two].position_index;
		mutual_index[index_two].cul_value = intermidate_one;
		mutual_index[index_two].position_index = intermidate_two;
		position_index[mutual_index[index_two].position_index] = index_two;
		position_index[mutual_index[index_one].position_index] = index_one;
	}
	void heap_initial()//��ʼ���ѣ���������������е��в������֮������
	{
		int k, i = 0;
		int current_min;
		for (i = (current_heap_number - 1) / 2; i >= 0; i--)
		{
			k = i;
			while (2 * k + 1 <= current_heap_number)
			{
				current_min = mutual_index[k].cul_value;
				current_min = current_min < mutual_index[2 * k + 1].cul_value ? current_min : mutual_index[2 * k + 1].cul_value;
				if (2 * k + 2 <= current_heap_number)
				{
					current_min = current_min < mutual_index[2 * k + 2].cul_value ? current_min : mutual_index[2 * k + 2].cul_value;
				}
				if (current_min == mutual_index[k].cul_value)
				{
					break;
				}
				else
				{
					if (current_min == mutual_index[2 * k + 1].cul_value)
					{
						swap_heap(k, 2 * k + 1);
						k = 2 * k + 1;
					}
					else
					{
						swap_heap(k, 2 * k + 2);
						k = 2 * k + 2;
					}
				}
			}
		}
	}
	void delete_minimal()//ɾ��������С��Ԫ��
	{
		int k;
		int current_min;
		if (current_heap_number != 0)
		{
			swap_heap(0, current_heap_number);//�������Ԫ�������Ԫ��
			current_heap_number--;//Ȼ�󽫶ѵĴ�С��������
			k = 0;
			while (2 * k + 1 <= current_heap_number)//Ȼ���������һЩά���ԵĹ���������ά����С��
			{
				current_min = mutual_index[k].cul_value;
				current_min = current_min < mutual_index[2 * k + 1].cul_value ? current_min : mutual_index[2 * k + 1].cul_value;
				if (2 * k + 2 <= current_heap_number)
				{
					current_min = current_min < mutual_index[2 * k + 2].cul_value ? current_min : mutual_index[2 * k + 2].cul_value;
				}
				if (current_min == mutual_index[k].cul_value)
				{
					return;
				}
				else
				{
					if (current_min == mutual_index[2 * k + 1].cul_value)
					{
						swap_heap(k, 2 * k + 1);
						k = 2 * k + 1;
					}
					else
					{
						swap_heap(k, 2 * k + 2);
						k = 2 * k + 2;
					}
				}
			}
		}
		else//���ֻʣ��һ��Ԫ�أ��ǾͲ���Ҫ���н�����ֱ�ӽ���Ԫ�صĸ�������һ
		{
			current_heap_number = -1;
		}
	}
	void heap_renew(int target_position, int new_value)//���ڵ�target_position�У����ж�������
	{
		int heap_target_position, k, current_min;
		heap_target_position = position_index[target_position];//�������һ���ڶ������ڵ�λ��
		k = heap_target_position;
		if (new_value < mutual_index[k].cul_value)//���ֵ�Ǽ��ٵģ���ֱ�ӽ��и�ֵ��Ȼ��ά���ѵ�����
		{
			mutual_index[k].cul_value = new_value;
			while (k > 0 && (mutual_index[(k - 1) / 2].cul_value > mutual_index[k].cul_value))//ά����
			{
				swap_heap((k - 1) / 2, k);
				k = (k - 1) / 2;
			}
			if (new_value == 0)//����Ǹ�ֵΪ0����Ӷ��н���ɾ������Ϊ����ÿ�β���һ��Ԫ�أ�����������һ��Ԫ��Ϊ0�����Կ϶�����Сֵ��
			{
				delete_minimal();
			}
		}
		else//����ֵ��������
		{
			mutual_index[k].cul_value = new_value;
			if (new_value == 1)//����µ�ֵ��1��������Ԫ�����¼������
			{
				current_heap_number++;//����ѵķ�Χ�����ǿ���֤�����¼�����е�Ԫ��һ�������ڶѵ�ĩβ����Ȼ������ɾ��������˳���Ƕ�Ӧ�෴��
				while (k > 0 && (mutual_index[(k - 1) / 2].cul_value > mutual_index[k].cul_value))//�����µ�ֵ��1�����Բ����ܱ���һ������
				{
					swap_heap((k - 1) / 2, k);
					k = (k - 1) / 2;
				}
			}
			else//�������1��˵���Ѿ��ڶ��У����Բ���Ҫ����ѵķ�Χ��ֱ�Ӹ�ֵ֮�����ά���ѽṹ����
			{
				while (2 * k + 1 <= current_heap_number)
				{
					current_min = mutual_index[k].cul_value;
					current_min = current_min < mutual_index[2 * k + 1].cul_value ? current_min : mutual_index[2 * k + 1].cul_value;
					if (2 * k + 2 <= current_heap_number)
					{
						current_min = current_min < mutual_index[2 * k + 2].cul_value ? current_min : mutual_index[2 * k + 2].cul_value;
					}
					if (current_min == mutual_index[k].cul_value)
					{
						break;
					}
					else
					{
						if (current_min == mutual_index[2 * k + 1].cul_value)
						{
							swap_heap(k, 2 * k + 1);
							k = 2 * k + 1;
						}
						else
						{
							swap_heap(k, 2 * k + 2);
							k = 2 * k + 2;
						}
					}
				}
			}
		}
	}
	void node_heap_decrease(int node_index)//����һ������������ڵ��е�ɾ������Ϊһ����һ�����ĸ�Ԫ�أ����������У����Ƕ������еĶ��������м���1
	{
		int leftmost_node;//��ǰ�ڵ������е�����ڵ������
		leftmost_node = node_index - (node_index % 4);
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value - 1);
		leftmost_node++;
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value - 1);
		leftmost_node++;
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value - 1);
		leftmost_node++;
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value - 1);
	}
	void node_heap_increase(int node_index)//��������ٵ�˳���Ǹպ��෴��
	{
		int leftmost_node;//��ǰ�ڵ������е����ҽڵ������
		leftmost_node = node_index - (node_index % 4) + 3;
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value + 1);
		leftmost_node--;
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value + 1);
		leftmost_node--;
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value + 1);
		leftmost_node--;
		heap_renew(total_nodes[leftmost_node].column, mutual_index[position_index[total_nodes[leftmost_node].column]].cul_value + 1);
	}
	void insert_row(int current_row_index, int current_column_index, int value)
	{
		int current_leftmost = avail_node_index;
		avail_node_index += 4;
		int column_index;
		column_index = current_row_index * 9 + value - 1;
		total_nodes[current_leftmost].column = column_index;
		total_nodes[current_leftmost].down = column_index;
		total_nodes[current_leftmost].up = total_nodes[column_index].up;
		total_nodes[total_nodes[column_index].up].down = current_leftmost;
		total_nodes[column_index].up = current_leftmost;
		mutual_index[column_index].cul_value++;
		current_leftmost++;
		column_index = 81 + current_column_index * 9 + value - 1;
		total_nodes[current_leftmost].column = column_index;
		total_nodes[current_leftmost].down = column_index;
		total_nodes[current_leftmost].up = total_nodes[column_index].up;
		total_nodes[total_nodes[column_index].up].down = current_leftmost;
		total_nodes[column_index].up = current_leftmost;
		mutual_index[column_index].cul_value++;
		current_leftmost++;
		column_index = 162 + ((current_row_index / 3) * 3 + current_column_index / 3) * 9 + value - 1;
		total_nodes[current_leftmost].column = column_index;
		total_nodes[current_leftmost].down = column_index;
		total_nodes[current_leftmost].up = total_nodes[column_index].up;
		total_nodes[total_nodes[column_index].up].down = current_leftmost;
		total_nodes[column_index].up = current_leftmost;
		mutual_index[column_index].cul_value++;
		current_leftmost++;
		column_index = 243 + current_row_index * 9 + current_column_index;
		total_nodes[current_leftmost].column = column_index;
		total_nodes[current_leftmost].down = column_index;
		total_nodes[current_leftmost].up = total_nodes[column_index].up;
		total_nodes[total_nodes[column_index].up].down = current_leftmost;
		total_nodes[column_index].up = current_leftmost;
		mutual_index[column_index].cul_value++;
	}
	void print_result()//��ӡ�����
	{
		int i, j, k, current_index;
		int m, n;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				input[i][j] = 0;
			}
		}
		for (m = 0; m < stack_index; m++)
		{
			current_index = node_stack[m] - node_stack[m] % 4;
			k = total_nodes[current_index].column % 9;
			i = (total_nodes[current_index].column - total_nodes[current_index].column % 9) / 9;
			current_index++;
			j = (total_nodes[current_index].column - total_nodes[current_index].column % 9 - 81) / 9;
			input[i][j] = k + 1;
		}
	}
	void creat_dlx_sudoku()//���þ���������ʮ������
	{
		int i, j, k;
		int row_position[9][9];//�������
		int column_position[9][9];//�������
		int small_position[9][9];//�����ÿһ��С����
		initial();
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				row_position[i][j] = 1;
				column_position[i][j] = 1;
				small_position[i][j] = 1;
			}

		}
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (input[i][j] != 0)
				{
					row_position[i][input[i][j] - 1] = 0;
					column_position[j][input[i][j] - 1] = 0;
					small_position[(i / 3) * 3 + j / 3][input[i][j] - 1] = 0;
				}
			}
		}
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (input[i][j] != 0)
				{
					insert_row(i, j, input[i][j]);
				}
				else
				{
					for (k = 0; k < 9; k++)
					{
						if ((row_position[i][k] * column_position[j][k] * small_position[(i / 3) * 3 + j / 3][k]) == 1)
						{
							insert_row(i, j, k + 1);
						}
						else
						{
							//do nothing
						}
					}
				}
			}
		}
		heap_initial();
	}
	void in_stack(int target_to_stack)
	{
		int leftmost = target_to_stack - target_to_stack % 4;
		for (int i = 0; i < 4; i++)//���ڵ�ǰ�е�ÿһ��
		{
			int current_column_traversal = leftmost + i;
			current_column_traversal = total_nodes[current_column_traversal].down;
			while (current_column_traversal != leftmost + i)//ɾ����ǰ���ཻ����
			{
				if (current_column_traversal != total_nodes[current_column_traversal].column)//������ͷ��
				{
					int temp_node = current_column_traversal - current_column_traversal % 4 - 1;
					for (int j = 0; j < 4; j++)
					{
						temp_node++;
						if (temp_node != current_column_traversal)
						{
							total_nodes[total_nodes[temp_node].down].up = total_nodes[temp_node].up;
							total_nodes[total_nodes[temp_node].up].down = total_nodes[temp_node].down;
						}
					}
					node_heap_decrease(temp_node);
				}
				current_column_traversal = total_nodes[current_column_traversal].down;
			}
		}
		node_heap_decrease(target_to_stack);//���Ե�ǰ�н���ɾ��
		node_stack[stack_index++] = target_to_stack;//Ȼ�������ջ
		available_column -= 4;
		//print_result();
	}
	void out_stack()//ע���ջ��ʱ�����෴�Ĳ���������ɾ�����෴
	{
		int target_to_stack = node_stack[--stack_index];
		int rightmost = target_to_stack - target_to_stack % 4 + 3;
		for (int i = 0; i < 4; i++)//���ڵ�ǰ�е�ÿһ��
		{
			int current_column_traversal = rightmost - i;
			current_column_traversal = total_nodes[current_column_traversal].up;
			while (current_column_traversal != rightmost - i)//ɾ����ǰ���ཻ����
			{
				if (current_column_traversal != total_nodes[current_column_traversal].column)//������ͷ��
				{
					int temp_node = current_column_traversal - current_column_traversal % 4 + 4;
					for (int j = 0; j < 4; j++)
					{
						temp_node--;
						if (temp_node != current_column_traversal)
						{
							total_nodes[total_nodes[temp_node].down].up = temp_node;
							total_nodes[total_nodes[temp_node].up].down = temp_node;
						}
					}
					node_heap_increase(temp_node);
				}
				current_column_traversal = total_nodes[current_column_traversal].up;
			}
		}
		node_heap_increase(target_to_stack);//���Ե�ǰ�н��лظ�
		available_column += 4;
		//print_result();
	}
	int find_next()//��������һ��������ջ��Ԫ�أ�����޷���ջ�����Ѿ��ҵ��˽⣬�򷵻ز����л��ݲ���
	{
		int target_position;
		int temp_node_one;
		if (available_column == current_heap_number)
		{
			if (available_column == -1)
			{
				//print_result();
				return 2;
			}
			else
			{
				target_position = mutual_index[0].position_index;
				temp_node_one = total_nodes[target_position].down;
				in_stack(temp_node_one);
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}
	void seek_sudoku()
	{
		int find_result = 0;
		int temp_node_one;
		while (1)
		{
			find_result = find_next();
			if (!find_result)//����޷���ջ��Ŀǰû���ҵ��⣬���ջ
			{
				temp_node_one = node_stack[stack_index - 1];
				out_stack();
				temp_node_one = total_nodes[temp_node_one].down;
				while ((temp_node_one == total_nodes[temp_node_one].column))//�����ǰԪ���ǵ�ǰ��ͷ�ڵ㣬��ݹ��ջ
				{
					if (stack_index == 0)//���ջ�գ������е������ռ��Ѿ�������ȫ ����
					{
						return;
					}
					else
					{
						temp_node_one = node_stack[stack_index - 1];
						out_stack();
						temp_node_one = total_nodes[temp_node_one].down;
					}
				}
				in_stack(temp_node_one);//����ѡԪ����ջ
			}
			else
			{
				if (find_result / 2)//����Ѿ��ҵ�������򷵻أ���ʵ�����ǿ��Ը�������߼���Ӧ���ж����������������ȫ����ӡ
				{
					return;
				}
			}
		}
	}
	void set_input(vector<vector<char>> char_input)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (char_input[i][j] == '.')
				{
					input[i][j] = 0;
				}
				else
				{
					input[i][j] = char_input[i][j] - '1' + 1;
				}
			}
		}
	}
	void set_output(vector<vector<char> > &board)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				board[i][j] = input[i][j] + '1' - 1;
			}
		}
	}
	void solveSudoku(vector<vector<char> > &board)
	{
		set_input(board);
		creat_dlx_sudoku();
		seek_sudoku();
		print_result();
		set_output(board);
	}
};