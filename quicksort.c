/*
Homework #1
Student: Luis Rizo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomindex(k) (rand() % k);

struct listnode { struct listnode * next; long key; };

struct listnode * getNode(struct listnode * a, int idx);
struct listnode * sort(struct listnode * a);
long getLengthOfListnode(struct listnode * a);

int main(void)
{  
	const long MAX_ELEMENTS = 500000;
   long i, elements = MAX_ELEMENTS, count = 0;
   double time_spent;
   clock_t begin, end;
   struct listnode *node, *space;

   space =  (struct listnode *) malloc(MAX_ELEMENTS * sizeof(struct listnode));
   srand(time(NULL));
   while(count < 100) {
	    elements = MAX_ELEMENTS;
		begin = clock();
		printf("Begin: %lu | Elements: %ld", begin, elements);
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

struct listnode * sort(struct listnode * node){
	int i = 0;
	long length;
	struct listnode * pivot, * tmpNode, * smaller = NULL, * lastSmaller = NULL, * larger = NULL, * lastLarger = NULL;

	length = getLengthOfListnode(node);
	if (length > 1){
		i = randomindex(length);
		pivot = getNode(node, i);

		tmpNode = node;
		/* Make a single run through the node list */
		while(tmpNode) {
			/* Add node->key < pivot->key into `smaller`,
			 * If larger, add into `larger`.
			 * Ensure pivot is not added to either.
			 */
			if (tmpNode->key < pivot->key) {
				if (!smaller) smaller = lastSmaller = tmpNode;
				else lastSmaller = lastSmaller->next = tmpNode;
			} else if (tmpNode != pivot) { // Check for address equality
				if (!larger) larger = lastLarger = tmpNode;
				else lastLarger = lastLarger->next = tmpNode;
			}
			tmpNode = tmpNode->next;
		}
		/* Add pivot at the end of smaller */
		if (lastSmaller) lastSmaller = lastSmaller->next = pivot;
		else smaller = lastSmaller = pivot;
		/* Make last elements on smaller and larger point to NULL */
		lastSmaller->next = NULL;
		if (lastLarger) lastLarger->next = NULL;
		/* Sort smaller and larger separately */
		smaller = sort(smaller);
		larger = sort(larger);
		/* Join smaller and larger back together */
		lastSmaller = smaller;
		/* Find last smallest */
		while(lastSmaller->next != NULL) {lastSmaller = lastSmaller->next;}
		lastSmaller->next = larger;
		node = smaller;
	}
	return node;
}