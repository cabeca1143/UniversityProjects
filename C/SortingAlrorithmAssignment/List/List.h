#include <stdbool.h>

typedef struct
{
    long CurrentSize;
    long CurrentMemorySize;
    long Count;
    int* Array;
}List;
List* ListConstructor();
void ListAppend(List* array, int value);
void ListPrintElements(List* list);
bool ListContains(List* list, int num);
void ListBubbleSort(List* list);
void ListBubbleSortDescending(List* list);
void ListBubbleSortRecursive(List* list);
int ListIndexOf(List* list, int num);
void ListDebug(List* array);
void ListMergeSort(List* l);
void ListQuickSort(List* l);