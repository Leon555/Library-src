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
    ListNode *reverseKGroup(ListNode *head, int k) {
		struct ListNode **list = (struct ListNode **) malloc (sizeof(struct ListNode*) * k);
		struct ListNode *node = head;
        
		int i = 0;
		while(i < k && node) {
			list[i++] = node;
			node = node->next;
		}
        if(i < k)
            return head;
        
		for(i = 0; i < k/2; i++){
			struct ListNode* temp = list[i]->next;
			list[i]->next = list[k-i-1]->next;
			list[k-i-1]->next = temp;
            if(i>0)
                list[i-1]->next = list[k-i-1];
            if(k-i-2>=0)
                list[k-i-2]->next = list[i];
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
	sol.reverseKGroup(node, 2);

	while(node){
		printf("%d - ", node->val);
		node = node->next;
	}

}
