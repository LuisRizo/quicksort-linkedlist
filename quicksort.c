/*
Homework #1
Student: Luis Rizo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct listnode { struct listnode * next; long key; };

void printAddress(struct listnode * p) { printf("%p\n", p); }

int randomindex(int k) { return (rand() % k); }

void swapNodes(struct listnode ** list, int i1, int i2);
struct listnode * getNode(struct listnode * a, int idx);
long getLengthOfListnode(struct listnode * a);
struct listnode * sort(struct listnode * a);
void printListnode(struct listnode * list);

int main(void)
{  
   long i, max_reps = 5000;
   struct listnode *node, *space;
   space =  (struct listnode *) malloc(max_reps * sizeof(struct listnode));
   while(1) {
   		srand(time(NULL));
		for( i=0; i< max_reps; i++ )
		{  (space + i)->key = 2*((17*i)%max_reps);
			(space + i)->next = (space + (i+1));
		}
		(space+max_reps - 1)->next = NULL;
		node = space;
		printf("\n prepared list, now starting sort\n");
		node = sort(node);
		printf("\n checking sorted list\n");
		for( i=0; i < max_reps; i++)
		{  if( node == NULL )
			{  printf("List ended early | %ld\n", i); exit(0);
			}
			if( node->key != 2*i )
			{  printf("Node contains wrong value, %ld\n", i); exit(0);
			}
			node = node->next;
		}
		printf("Sort successful\n");
   }
   exit(0);
}

void printListnode(struct listnode * list) {
	int i = 0;
	int length = getLengthOfListnode(list);
	for(i = 0; i < length; i++) {
		printf("%ld,", getNode(list, i)->key);
	}
	printf("\n");
}

struct listnode * getNode(struct listnode * tmp, int idx) {
	int i = 0;
	struct listnode * a = tmp;
	while(a && i < idx) {
		a = a->next;
		i++;
	}
	if (!a) {
		printf("Get node returned a null value when asked for index %d.\n", idx);
		printListnode(tmp);
	}
	return a;
}

long getLengthOfListnode(struct listnode * a) {
	long length = 0;
	struct listnode * temp = a;
	while(temp) {
		temp = temp->next;
		length++;
	}
	return length;
}

void swapNodes(struct listnode ** list, int idx1, int idx2) {
	struct listnode * node, * val, * prevNode, * prevVal, * tmp;
	if (idx1 == idx2) return;
	int i1 = idx1, i2 = idx2;
	node = getNode(*list, i1);
	val = getNode(*list, i2);
	if (!node || !val) return;

	prevNode = getNode(*list, i1 - 1);
	prevVal = getNode(*list, i2 - 1);

	if (i1 != 0 && prevNode)
		prevNode->next = val;
	else
		*list = val;

	if (i2 != 0 && prevVal)
		prevVal->next = node;
	else
		*list = node;

	tmp = val->next;
	val->next = node->next;
	node->next = tmp;
}

struct listnode * sort(struct listnode * node){
	int i, j1, j2;
	long length;
	struct listnode * pivot;

	length = getLengthOfListnode(node);
	if (length > 1){
		i = randomindex(length);
		pivot = getNode(node, i);

		swapNodes(&node, i, length - 1);

		j1 = 0; j2 = length - 1;
		while(j1 < j2) {
			for(; getNode(node, j1)->key < pivot->key; j1++);
			for(; getNode(node, j2)->key >= pivot->key && j2 > j1; j2--);
			
			if (j1 != j2) {
				swapNodes(&node, j1, j2);
			}
		}
		swapNodes(&node, length - 1, j1);

		if (j1 != 0) getNode(node, j1 - 1)->next = NULL;
		sort(node);
		sort(pivot);
		if (j1 != 0) getNode(node, j1 - 1)->next = pivot;
	}
	return node;
}

