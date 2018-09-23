# quicksort-linkedlist

## Requirements

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

## Testing

In order to run this program, you need to have a C/C++ compiler.
I use `gcc` or `g++` installed, and the shell command I write to run `quicksort.c` is:

```sh
gcc -Wall -o output quicksort.c && ./output
```