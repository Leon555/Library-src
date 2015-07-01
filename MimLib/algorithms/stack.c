#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "stack.h"

stack *stack_init(size_t len)
{
	stack *st = (stack*) malloc (sizeof(stack));
	
	st->array = (stack_node**) calloc (len, sizeof(stack_node*));

	st->capacity = len;
	st->size = 0;
	st->top = -1;

	return st;
}

void stack_destroy(stack *st)
{
	free(st->array);
}

int stack_empty(stack *st)
{
	return ((st->size) ? 0 : 1);
}

void stack_push(stack *st, stack_node *e)
{
	if(st->size == st->capacity)
		st->array = (stack_node **)realloc(st->array, st->capacity * 2 * sizeof(stack_node *));

	st->top++;
	st->array[st->top] = e;
	st->size++;
}

stack_node *stack_pop(stack *st)
{
	if(st->size) {
        st->size--;
	    return st->array[st->top--];
    }

	return NULL;
}

int main()
{
    return 0;
}
