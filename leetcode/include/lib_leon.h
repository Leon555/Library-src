#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct BiNode;

typedef struct BiNode {
	int value;
	struct BiNode *left;
	struct BiNode *right;
	struct BiNode *parent;
}BiNode;

typedef struct BiSearchTree {
	BiNode *root;
}BiSearchTree;

typedef BiNode stack_node;
typedef struct stack {
	size_t capacity;
	size_t size;
	ssize_t top;
	stack_node **array;
}stack;

typedef int list_node;
struct ListNode;

typedef struct ListNode {
	list_node val;
	struct ListNode *next;
	struct ListNode *prev;
}ListNode;

void print_array(int *array, size_t len);
void init_array(int **array, size_t len, int positive);

stack *stack_init(size_t len);
void stack_destroy(stack *st);
int stack_empty(stack *st);
stack_node *stack_pop(stack *st);
void stack_push(stack *st, stack_node *e);

