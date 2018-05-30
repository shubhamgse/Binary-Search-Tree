#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

int i = 0;
int clone = 0;
int incr;
Tree * newTree(){
	
	Tree * t = malloc(sizeof(Tree));
	t->root = NULL;
	t->insert=insertTree;
	t->insertn = insertNode;
	t->search=searchTree;
	t->searchN=searchNode;
	t->sort=sortBST;
	t->sortn=traverse;
	t->clone=cloneTree;
	t->compare=compare;
	t->removeData=removeBST;
	t->delete=delete;
	return t;
}


Node * newNode(Data d, Node * parent){
	
	Node * n = malloc(sizeof(Node));
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	n->data = d;
	return n;

}

Data * insertNode(Node * n, Data d){
	
	
	if(n->data.value == d.value)
			return NULL;
	if(n->data.value < d.value){
		if(n->right == NULL){
			n->right = malloc(sizeof(Node));
			n->right->left = n->right->right = NULL;
			n->right->parent = n;
			n->right->data = d;
			return &n->right->data;
		}
		
		else{
			insertNode(n->right, d);
		}
	
	}
	else if(n->data.value > d.value){
		if(n->left == NULL){
			n->left = malloc(sizeof(Node));
			n->left->left = n->left->right = NULL;
			n->left->parent = n;
			n->left->data = d;
			return &n->left->data;
		}

		else{
			insertNode(n->left, d);
		}
	
	
	}


}

Data * insertTree(Tree* bst,Data d){
	
	if(bst->root == NULL){
		
		bst->root = malloc(sizeof(Node));
		bst->root->left=bst->root->right =NULL;
		bst->root->data = d;
		return &bst->root->data;
	}
	else{
		insertNode(bst->root, d);
	}
	
}

Data * sortBST(Tree * bst, Data * test){
	
	
	
	if(bst->root == NULL){
	return NULL;
	}
	
	traverse(bst->root, test);
	return test;
}


Node * traverse(Node * n, Data * test){
	
	if(n != NULL){
		
		traverse(n->left, test);
		
		test[i++] = n->data;
		traverse(n->right, test);
		
	}
	return n;
}

Node * searchNode(Node * n, Data d){
	
	
	if(n->data.value == d.value)
		return n;
	
	
	if(n->data.value < d.value){
		if(n->right == NULL){
			return NULL;
		}
		else{
			return searchNode(n->right, d);
		}
	
	}
	else if(n->data.value > d.value){
		if(n->left == NULL){
			return NULL;
		}
		else{
			return searchNode(n->left, d);
		}
	
	
	}
	else{
		return NULL;
	}

}

Data * searchTree(Tree* bst, Data d){
	Node * n;
	if(bst->root == NULL){
			
			return NULL;
			
		}
		else{
			
			n = searchNode(bst->root, d);
			
		}
	return &(n->data);
}

Node * cloneNode(Node * n, Data * d){
		
	if(n != NULL){
		d[clone++] = n->data;
		cloneNode(n->left, d);
		cloneNode(n->right, d);
	}
	return n;
}
void copyNode(Node * n, Data * d){

	if(n != NULL){
		d[incr++] = n->data;
		copyNode(n->left, d);
		copyNode(n->right, d);
	}
	return;
}

Tree * cloneTree(Tree * tr){
	
	if(tr->root == NULL){
		return NULL;
	}
	Data d[13];
	cloneNode(tr->root, d);
	Tree * t = newTree();
	for(int i = 0; i<13; i++){
		t->insert(t, d[i]);
	}
	return t;
}


int size(Node * n){
	
	if(n == NULL)
		return 0;
	
	else	
		return (size(n->left)+1+size(n->right));
	
}


int compare(Tree * t, Tree * copy){
	int check = 0;
	if(t == NULL || copy == NULL){
		return 0;
	}
	else{                   // No need of this else part t->root and copy->root can be directly passed
		
		Data d1[13], d2[13];
	
	if(t->root != NULL){
		incr = 0;
		copyNode(t->root, d1);
	}
	if(copy->root != NULL){
		incr = 0;
		copyNode(copy->root, d2);
	}
	
	int l = size(copy->root);
	
	for(int i = 0; i<l; i++){
		//printf("Compare1 : %d\n",d1[i].value);
		//	printf("Compare2 : %d\n",d2[i].value);
		if(d1[i].value == d2[i].value){
			
			check = 1;
		}
		else{
			check = 0;
			return check;
		}
			
	}
	return check;
	}
}


void removeLeaf(Tree * bst, Node * leaf){
	if(leaf->parent == NULL)
		bst->root = NULL;
	else if(leaf == leaf->parent->left)
		leaf->parent->left = NULL;
	else
		leaf->parent->right = NULL;

	free(leaf);
	
}



void shortCircuit(Tree * bst, Node * n){

	if(bst->root == n){
		if(n->right != NULL){
			bst->root = NULL;
			bst->root = n->right;
			bst->root->parent = NULL;
		}
		else{
			bst->root = NULL;
			bst->root = n->left;
			bst->root->parent = NULL;
		}
		free(n);
	}

	else if(n == n->parent->left){
		if(n->left != NULL){
			//n is left, child is left
			n->parent->left = n->left;
			n->left->parent = n->parent;
		}
		else{
			//n is left, child is right
			n->parent->left = n->right;
			n->right->parent = n->parent;
		}
		free(n);
	}
	else{
		if(n->left != NULL){
			//n is right, child is left
			n->parent->right = n->left;
			n->left->parent = n->parent;
		}
		else{
			//n is right, child is right
			n->parent->right = n->right;
			n->right->parent = n->parent;
		}
		free(n);
	}
	
}


Node * findRightMin(Node * n){

	n = n->right;
	
	while(n->left != NULL){
	
	n = n->left;
	
	}
	
	return n;

}


void promotion(Tree * bst, Node * n){
	Node * toPromote = findRightMin(n);
	
	n->data = toPromote->data;
	n=toPromote;
	if(toPromote->left == NULL && toPromote->right == NULL){
		//fprintf(stderr,"Performing remove Leaf");
		removeLeaf(bst, toPromote);
	}
	else{
		
		shortCircuit(bst, toPromote);
	}
}



void removeBST(Tree * bst, Data value){
	
	Node * toDelete = searchNode(bst->root, value);
	
	if(toDelete != NULL){
		
		if(toDelete->left == NULL && toDelete->right == NULL)
			removeLeaf(bst, toDelete);	
		else if(toDelete->left == NULL || toDelete->right == NULL){
			//fprintf(stderr,"Performing shortCircuit Leaf");
			shortCircuit(bst, toDelete);}
		else
			promotion(bst, toDelete);
		
	}
	
}

void deleteTree(Node *n){
 if(n!=NULL){
  deleteTree(n->left);
  deleteTree(n->right);
  free(n);
  
 }
 return;
}
void delete(Tree * bst){
 if(bst->root != NULL){
  deleteTree(bst->root);
  free(bst);
 }
 else
 	free(bst);
}