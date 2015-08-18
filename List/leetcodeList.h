#include <list>
#include <stdint.h>
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution
{
public:
	uint64_t from_list_to_number(const ListNode* num_list)
	{
		uint64_t result = 0;
		uint64_t bit_carry = 1;
		const ListNode* temp_iter = num_list;
		while (temp_iter != nullptr)
		{
			result = result  + temp_iter->val*bit_carry;
			temp_iter = temp_iter->next;
			bit_carry *= 10;
		}
		return result;
	}
	ListNode* from_number_to_list(uint64_t number)
	{
		ListNode* fake_head = new ListNode(0);
		ListNode* tail = fake_head;
		uint64_t temp_bit;
		if (number == 0)
		{
			return fake_head;
		}
		while (number > 0)
		{
			temp_bit = number % 10;
			number = number / 10;
			ListNode* temp_node = new ListNode(temp_bit);
			tail->next = temp_node;
			tail = temp_node;
		}
		ListNode* result = fake_head->next;
		delete fake_head;
		return result;
	}
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		uint64_t number_1, number_2;
		number_1 = from_list_to_number(l1);
		number_2 = from_list_to_number(l2);
		return from_number_to_list(number_1 + number_2);
	}
};