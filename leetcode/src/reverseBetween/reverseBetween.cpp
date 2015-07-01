/**
  * Definition for singly-linked list.
  * struct ListNode {
  *     int val;
  *     ListNode *next;
  *     ListNode(int x) : val(x), next(NULL) {}
  * };
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x)
		:val(x), next(NULL)
	{
	}
};

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
		m--;
		n--;
		int len = n-m+1;
		struct ListNode **list = (struct ListNode **) malloc (sizeof(struct ListNode*) * len);
		int i = 0;
		struct ListNode *node = head;
		while(i < m) {
			node = node->next;
			i++;
		}
		while(i <= n){
			list[i-m] = node;
			node = node->next;
			i++;
		}
		for(i = 0; i <= (n-m)/2; i++){
			int temp = list[i]->val;
			list[i]->val = list[len-i-1]->val;
			list[len-i-1]->val = temp;
		}

		return head;
    }
};

int main(int argc, char* argv[])
{
	int len = 10;
	struct ListNode **list = (struct ListNode **) malloc (sizeof(struct ListNode *) * len);

	for(int i = 0; i < len ; i++) {
		list[i] = (struct ListNode *) malloc (sizeof(struct ListNode));
		list[i]->val = i;
	}

	for(int i = 0; i < len-1; i++)
		list[i]->next = list[i+1];

	struct ListNode *node = list[0];

	while(node){
		printf("%d - ", node->val);
		node = node->next;
	}

	node = list[0];

	//free(list);

	Solution sol;
	//sol.reverseBetween(node, 1, 1);
	//sol.reverseBetween(node, 1, 2);
	//sol.reverseBetween(node, 1, 5);
	//sol.reverseBetween(node, 1, 5);
	sol.reverseBetween(node, 2, 6);

	while(node){
		printf("%d - ", node->val);
		node = node->next;
	}

}
