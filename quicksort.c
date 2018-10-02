/*
Homework #1
Student: Luis Rizo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomindex(k) (rand() % k);

struct listnode { struct listnode * next; long key; };
void printAddress(struct listnode * p) { printf("%p\n", p); }

struct listnode * getNode(struct listnode * a, int idx);
struct listnode * sort(struct listnode * a);

long getLengthOfListnode(struct listnode * a);

void swapNodes(struct listnode ** list, int i1, int i2);
void printListnode(struct listnode * list);

int main(void)
{  
	const long MAX_ELEMENTS = 500000;
   long i, elements = MAX_ELEMENTS, count = 0;
   double time_spent;
   clock_t begin, end;
   struct listnode *node, *space;

   space =  (struct listnode *) malloc(MAX_ELEMENTS * sizeof(struct listnode));
   while(count < 1) {
	    elements = MAX_ELEMENTS - count;
		begin = clock();
		printf("Begin: %lu | Elements: %ld", begin, elements);
   		srand(time(NULL));
		for( i=0; i < elements; i++ )
		{  (space + i)->key = 2*((17*i)%elements);
			(space + i)->next = (space + (i+1));
		}
		(space+elements - 1)->next = NULL;
		node = space;
		printf("\n prepared list, now starting sort\n");
		node = sort(node);
		printf("\n checking sorted list\n");
		for( i=0; i < elements; i++)
		{  if( node == NULL )
			{  printf("List ended early | %ld\n", i); exit(0);
			}
			if( node->key != 2*i )
			{  printf("Node contains wrong value, %ld\n", i); exit(0);
			}
			node = node->next;
		}
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Sort #%ld successful in %f seconds\n", count, time_spent);
		count++;
   }
   exit(0);
}

void printListnode(struct listnode * list) {
	int i = 0, length = getLengthOfListnode(list);
	for(i = 0; i < length; i++) {
		printf("%ld,", getNode(list, i)->key);
	}
	printf("\n");
}

struct listnode * getNode(struct listnode * a, int idx) {
	int i = 0;
	struct listnode * tmp = a;
	if (idx < 0) {
		return NULL;
	}
	while(tmp && i < idx) {
		tmp = tmp->next;
		i++;
	}
	return tmp;
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

void swapNodes(struct listnode ** list, int i1, int i2) {
	struct listnode * node, * val, * prevNode, * prevVal, * tmp;
	if (i1 == i2) return;
	prevNode = getNode(*list, i1 - 1);
	prevVal = getNode(*list, i2 - 1);
	node = prevNode->next;
	val = prevVal->next;
	if (!node || !val) return;

	if (prevNode)
		prevNode->next = val;
	else
		*list = val;

	if (prevVal)
		prevVal->next = node;
	else
		*list = node;

	tmp = val->next;
	val->next = node->next;
	node->next = tmp;
}

struct listnode * sort(struct listnode * node){
	int i = 0, j1, j2;
	long length;
	struct listnode * pivot, * tmp;

	length = getLengthOfListnode(node);
	if (length > 1){
		i = randomindex(length);
		pivot = getNode(node, i);
		swapNodes(&node, i, length - 1);

		j1 = 0; j2 = length - 1;
		tmp = node;
		while(tmp && j1 < j2) {
			while(tmp->key < pivot->key) {
				j1++;
				if (tmp->next->key >= pivot->key) {
					break;
				}
				tmp = tmp->next;
			}
			for(; getNode(node, j2)->key >= pivot->key && j2 > j1; j2--);
			
			if (j1 != j2) {
				swapNodes(&node, j1, j2);
				tmp = getNode(node, j1); // Update pointer after swap.
			}
		}
		swapNodes(&node, length - 1, j1);
		if (j1 == 0) {
			pivot = node->next;
			j1++;
		}
		getNode(node, j1 - 1)->next = NULL;
		node = sort(node);
		pivot = sort(pivot);
		getNode(node, j1 - 1)->next = pivot;
	}
	return node;
}

