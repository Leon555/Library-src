#ifndef MIM_DATA_STRUCTURES_H
#define MIM_DATA_STRUCTURES_H

#include "binary_node.h"

typedef struct BiSearchTree {
	BiNode *root;
}BiSearchTree;

typedef int list_node;
struct ListNode;

typedef struct ListNode {
	list_node val;
	struct ListNode *next;
	struct ListNode *prev;
}ListNode;

#endif // MIM_DATA_STRUCTURES_H
