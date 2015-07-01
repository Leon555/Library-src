#ifndef MIM_BINARY_NODE_H
#define MIM_BINARY_NODE_H

struct BiNode;

typedef struct BiNode {
	int value;
	struct BiNode *left;
	struct BiNode *right;
	struct BiNode *parent;
}BiNode;

#endif // MIM_BINARY_NODE_H