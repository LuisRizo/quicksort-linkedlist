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

void debugCrash(int n) { //printf("Crash Spot #%d", n); 
}

void swapNodes(struct listnode ** list, int i1, int i2);
struct listnode * getNode(struct listnode * a, int idx);
long getLengthOfListnode(struct listnode * a);
struct listnode * sort(struct listnode * a);
void printListnode(struct listnode * list);

int main(void)
{  
	// char buffer[65536];
   long i, max_reps = 500, count = 0;
   double time_spent;
   clock_t begin, end;
   struct listnode *node, *space;
	// setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));

   space =  (struct listnode *) malloc(max_reps * sizeof(struct listnode));
   while(count < 1) {
		begin = clock();
		printf("Begin: %lu", begin);
   		srand(2012);
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
		debugCrash(11);
		printf("%ld,", getNode(list, i)->key);
	}
	printf("\n");
}

struct listnode * getNode(struct listnode * a, int idx) {
	int i = 0;
	struct listnode * tmp = a;
	if (idx < 0) return NULL;
	while(tmp && i < idx) {
		// debugCrash(12);
		tmp = tmp->next;
		i++;
	}
	if (!tmp) {
		printf("Get node returned a null value when asked for index %d.\n", idx);
		printListnode(a);
	}
	return tmp;
}

long getLengthOfListnode(struct listnode * a) {
	long length = 0;
	struct listnode * temp = a;
	while(temp) {
		// debugCrash(1);
		temp = temp->next;
		length++;
	}
	
	return length;
}

void swapNodes(struct listnode ** list, int i1, int i2) {
	struct listnode * node, * val, * prevNode, * prevVal, * tmp;
	if (i1 == i2) return;
	node = getNode(*list, i1);
	val = getNode(*list, i2);
	if (!node || !val) return;

	prevNode = getNode(*list, i1 - 1);
	prevVal = getNode(*list, i2 - 1);

	if (prevNode){
		// debugCrash(2);
		prevNode->next = val;
	}else
		*list = val;

	if (prevVal){
		// debugCrash(3);
		prevVal->next = node;
	}else
		*list = node;

	debugCrash(4);
	tmp = val->next;
	debugCrash(5);
	val->next = node->next;
	debugCrash(6);
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
			debugCrash(7);
			for(; getNode(node, j1)->key < pivot->key; j1++);
			debugCrash(8);
			for(; getNode(node, j2)->key >= pivot->key && j2 > j1; j2--);
			
			if (j1 != j2) {
				swapNodes(&node, j1, j2);
			}
		}
		swapNodes(&node, length - 1, j1);

		if (j1 != 0) {
			debugCrash(9);
			getNode(node, j1 - 1)->next = NULL;
		}
		sort(node);
		sort(pivot);
		if (j1 != 0) {
			debugCrash(10);
			getNode(node, j1 - 1)->next = pivot;
		}
	}
	return node;
}

