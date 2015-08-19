#include <list>
#include <stdint.h>
#include <vector>
#include <queue>
#include <functional>
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 using namespace std;
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
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		int length = 0;
		ListNode* hehe = head;
		while (hehe != nullptr)
		{
			length++;
			hehe = hehe->next;
		}
		int nth = length - n;
		length = 0;
		if (nth == 0)
		{
			return head->next;
		}
		else
		{
			ListNode* prev = head;
			ListNode* next = head->next;
			while (nth > 1)
			{
				nth--;
				prev = next;
				next = next->next;
			}
			prev->next = next->next;
			return head;
		}
		
	}
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode* fake_head = new ListNode(0);
		ListNode* tail = fake_head;
		ListNode* l1_head = l1;
		ListNode* l2_head = l2;
		while (l1_head != nullptr&&l2_head != nullptr)
		{
			if (l1_head->val < l2_head->val)
			{
				tail->next = l1_head;
				tail = l1_head;
				l1_head = l1_head->next;
				tail->next = nullptr;
			}
			else
			{
				tail->next = l2_head;
				tail = l2_head;
				l2_head = l2_head->next;
				tail->next = nullptr;
			}
		}
		if (l1_head == nullptr)
		{
			tail->next = l2_head;
		}
		else
		{
			tail->next = l1_head;
		}
		tail = fake_head->next;
		delete fake_head;
		return tail;
		
	}
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		struct list_cmp
		{
			bool operator()(ListNode* a, ListNode* b)
			{
				if (a->val > b->val)
				{
					return true;
				}
			}
		};
		priority_queue<ListNode*,vector<ListNode*>,list_cmp> List_queue;
		for (auto i : lists)
		{
			if (i != nullptr)
			{
				List_queue.push(i);
			}
			
		}
		ListNode* fake_head = new ListNode(0);
		ListNode* tail = fake_head;
		while (!List_queue.empty())
		{
			auto temp=List_queue.top();
			List_queue.pop();
			if (temp->next != nullptr)
			{
				List_queue.push(temp->next);
			}
			tail->next = temp;
			tail = temp;
			tail->next = nullptr;
		}
		tail = fake_head->next;
		delete fake_head;
		return tail;
	}
	ListNode* swapPairs(ListNode* head)
	{

		ListNode fake_head(0);
		ListNode* pfake_head = &fake_head;
		ListNode* temp_1;
		ListNode* temp_2;
		ListNode* tail;
		tail = pfake_head;
		temp_1 = head;
		while (temp_1)
		{
			temp_2 = temp_1->next;
			if (temp_2)
			{
				ListNode* next = temp_2->next;
				tail->next = temp_2;
				temp_2->next = temp_1;
				tail = temp_1;
				tail->next = nullptr;
				temp_1 = next;
			}
			else
			{
				tail->next = temp_1;
				temp_1 = nullptr;
			}
		}
		return pfake_head->next;
	}
	pair<int,ListNode*> findk(ListNode* head,int k)
	{
		int counter = 0;
		ListNode* trav_iter = head;
		ListNode* prev = nullptr;
		while (counter < k&&trav_iter != nullptr)
		{
			counter++;
			prev = trav_iter;
			trav_iter = trav_iter->next;
		}
		return make_pair(counter,prev);
	}
	ListNode* reverse(ListNode* head)
	{
		ListNode fake_head(0);
		ListNode* p_fake_head = &fake_head;
		while (head)
		{
			ListNode* next = head->next;
			head->next = p_fake_head->next;
			p_fake_head->next = head;
			head = next;
		}
		return p_fake_head->next;
	}
	ListNode* reverseKGroup(ListNode* head, int k)
	{
		ListNode fake_head(0);
		ListNode* p_fake_head = &fake_head;
		ListNode* tail = p_fake_head;
		ListNode* new_head = head;
		auto result = findk(new_head, k);
		while (result.first == k)
		{
			ListNode* temp_tail = new_head;
			ListNode* temp_new_head = result.second->next;
			result.second->next = nullptr;
			tail->next = reverse(new_head);
			new_head = temp_new_head;
			tail = temp_tail;
			result = findk(new_head, k);
		}
		tail->next = new_head;
		return p_fake_head->next;
	}
};
ListNode *rotateRight(ListNode *head, int k)
{
	if (!head || !head->next || k == 0)
	{
		return head;
	}
	int n = 0;
	ListNode *fast = head;
	ListNode* tail;
	while (fast)
	{
		n++;
		tail = fast;
		fast = fast->next;
	}

	if ((k = k%n) == 0)
	{
		return head;
	}
		

	fast = head;
	ListNode *slow;
	int count = 0;
	while (count<n-k-1)
	{
		fast = fast->next;
		count++;
	}
	slow = fast->next;
	fast->next = nullptr;
	tail->next = head;
	head = slow;
	

	return head;

}