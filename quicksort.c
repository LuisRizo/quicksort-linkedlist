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

void debugCrash(FILE * fptr, int n) { //fprintf(fptr, "Crash Spot #%d", n); 
}

void quit(FILE * fptr) {
	fclose(fptr);
	exit(0);
}

void swapNodes(FILE * fptr, struct listnode ** list, int i1, int i2);
struct listnode * getNode(struct listnode * a, int idx);
long getLengthOfListnode(struct listnode * a);
struct listnode * sort(FILE * fptr, struct listnode * a);
void printListnode(struct listnode * list);

int main(void)
{  
	FILE *fptr;
	// char buffer[65536];
   long i, max_reps = 500;
   double time_spent;
   clock_t begin, end;
   struct listnode *node, *space;
	fptr = fopen("quicksort.log", "w");
	if (fptr == NULL)
    {
        printf("File does not exists \n");
        exit(1);
    }
	// setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));

   space =  (struct listnode *) malloc(max_reps * sizeof(struct listnode));
   while(1) {
		begin = clock();
		// fprintf(fptr, "Begin: %lu", begin);
   		srand(2012);
		for( i=0; i< max_reps; i++ )
		{  (space + i)->key = 2*((17*i)%max_reps);
			(space + i)->next = (space + (i+1));
		}
		(space+max_reps - 1)->next = NULL;
		node = space;
		printf("\n prepared list, now starting sort\n");
		node = sort(fptr, node);
		printf("\n checking sorted list\n");
		for( i=0; i < max_reps; i++)
		{  if( node == NULL )
			{  printf("List ended early | %ld\n", i); quit(fptr);
			}
			if( node->key != 2*i )
			{  printf("Node contains wrong value, %ld\n", i); quit(fptr);
			}
			node = node->next;
		}
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Sort successful in %f seconds\n", time_spent);
   }
   quit(fptr);
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

void swapNodes(FILE * fptr, struct listnode ** list, int i1, int i2) {
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

	debugCrash(fptr, 4);
	tmp = val->next;
	debugCrash(fptr, 5);
	val->next = node->next;
	debugCrash(fptr, 6);
	node->next = tmp;
}

struct listnode * sort(FILE * fptr, struct listnode * node){

	int i, j1, j2;
	long length;
	struct listnode * pivot;

	// freopen("quicksort.log", "w", fptr);

	length = getLengthOfListnode(node);
	if (length > 1){
		i = randomindex(length);
		pivot = getNode(node, i);

		swapNodes(fptr, &node, i, length - 1);

		j1 = 0; j2 = length - 1;
		while(j1 < j2) {
			debugCrash(fptr, 7);
			for(; getNode(node, j1)->key < pivot->key; j1++);
			debugCrash(fptr, 8);
			for(; getNode(node, j2)->key >= pivot->key && j2 > j1; j2--);
			
			if (j1 != j2) {
				swapNodes(fptr, &node, j1, j2);
			}
		}
		swapNodes(fptr, &node, length - 1, j1);

		if (j1 != 0) {
			debugCrash(fptr, 9);
			getNode(node, j1 - 1)->next = NULL;
		}
		sort(fptr, node);
		sort(fptr, pivot);
		if (j1 != 0) {
			debugCrash(fptr, 10);
			getNode(node, j1 - 1)->next = pivot;
		}
	}
	return node;
}

