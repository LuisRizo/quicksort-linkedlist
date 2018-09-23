# quicksort-linkedlist

## Instructions

Implement the quicksort algorithm on lists. You write one function

```c
struct listnode * sort(struct listnode * a);
```

with

```c
struct listnode { struct listnode * next; int key;};
```

It takes a list, and returns the list in sorted sequence.
You change only pointers, do not allocate new nodes or move key values to different nodes.