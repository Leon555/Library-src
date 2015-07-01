#ifndef MIM_STACK_H
#define MIM_STACK_H

#include "data_structures.h"
#include "binary_node.h"

typedef BiNode stack_node;

typedef struct stack {
	size_t capacity;
	size_t size;
	ssize_t top;
	stack_node **array;
}stack;

stack *stack_init(size_t len);
void stack_destroy(stack *st);
int stack_empty(stack *st);
stack_node *stack_pop(stack *st);
void stack_push(stack *st, stack_node *e);

#endif // MIM_STACK_H