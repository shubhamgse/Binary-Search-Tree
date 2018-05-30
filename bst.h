#ifndef BST_H
#define BST_H
typedef struct Data{
	
	int value;

}Data;

typedef struct Node{
	
	Data data;
	struct Node * left, * right, * parent;

}Node;

typedef struct Tree{
	
	Node * root;
	
	Data * (*insert)(struct Tree*, Data);
	Data * (*insertn)(struct Node *,Data);
	Data * (*search)(struct Tree *, Data);
	Node * (*searchN)(struct Node *, Data);
	Data * (*sort)(struct Tree*, Data*);
    Node * (*sortn)(struct Node*, Data*);
	struct Tree * (*clone)(struct Tree*);
	int (*compare)(struct Tree *, struct Tree *);
	void (*removeData)(struct Tree *, Data);
	void (*delete)(struct Tree * bst);
	
}Tree;

Node * newNode(Data d, Node * parent);
Tree * newTree();
Data * insertTree(Tree*, Data);
Data * insertNode(Node*, Data);
Data * searchTree(Tree*, Data);
Node * searchNode(Node*, Data);
Data * sortBST(Tree *, Data *);
Node * traverse(Node *, Data *);
Tree * cloneTree(Tree *);
int compare(Tree *, Tree *);
void removeBST(Tree *, Data);
void delete(Tree * bst);
#endif