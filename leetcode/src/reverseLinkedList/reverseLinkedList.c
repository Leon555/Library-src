#include "lib_leon.h"

//reverse a singly-linked list and return the new head
ListNode* reverseSinglyLinkedList(ListNode *head)
{
	if(head == NULL || head->next == NULL)
		return head;

	ListNode *tmp;
	ListNode *pr = head;
	ListNode *p = head->next;
	head->next = NULL;

	while(p){
		tmp = p->next;
		p->next = pr;
		pr = p;
		p = tmp;
	}

	return pr;
}

int main(int argc, char *argv[])
{
	int i = 0;
	int caseNum = 5;
	ListNode *tmp = NULL;

	ListNode **heads = (ListNode **)malloc(caseNum * sizeof(ListNode *));
	
	//case 1: empty list
	//case 2: only 1 node
	//case 3: two nodes
	//case 4: three node
	//case 5: four nodes

	int j = 0;
	for(i = 0; i < caseNum; i++) {
		heads[i] = NULL;
		heads[i] = (ListNode *)malloc(sizeof(ListNode) * i);
		for(j = 0; j < i-1; j++) {
			heads[i][j].val = j;
			heads[i][j].next = &heads[i][j+1];
		}
		heads[i][j].val = j;
		heads[i][j].next = NULL;
			
		tmp = reverseSinglyLinkedList(heads[i]);
		printf("case %d: ", i);
		while(tmp) {
			printf("%d ", tmp->val);
			tmp = tmp->next;
		}
		printf("\n");
	}

	return 0;
}
