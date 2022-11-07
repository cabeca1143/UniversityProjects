#include "Functions.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

const int MAX_VALUE_SIZE = 100000;

List* GetListWithRandomElements(int size)
{
    srand(time(NULL));
    List* toReturn = ListConstructor();

    for (int i = 0; i < size; i++)
    {
        ListAppend(toReturn, rand() % MAX_VALUE_SIZE);
    }

    return toReturn;
}

List** GetThreeLists(int size)
{
    List** lists = malloc(sizeof(List) * 3);
    for (int i = 0; i < 3; i++)
    {
        lists[i] = GetListWithRandomElements(size);
    }
    return lists;
}

struct tm* GetTimeStruct()
{
    time_t seconds = time(NULL);
    return localtime(&seconds);
}

void ProcessSortingAlgorithm (void (*function)(List*), List** lists, char* functionName)
{
    float time = clock();
    for (int i = 0; i < 3; i++)
    {
        (*function)(lists[i]);
    }
    time = ((float)clock() - time) / (float)CLOCKS_PER_SEC;
    float avgTime = time / (float)3;

    struct tm* ts = GetTimeStruct();
    printf("[%d:%d:%d]%s took %f seconds with 3 arrays of %d items, with an average of %f seconds!\n",
           ts -> tm_hour, ts -> tm_min, ts -> tm_sec, functionName, time, lists[0] -> Count, avgTime);
}

void DoStuffSlow(int size)
{
    List** lists = GetThreeLists(size);
    ProcessSortingAlgorithm(ListBubbleSort, lists, "BubbleSort");

    free(lists);
    lists = GetThreeLists(size);
    ProcessSortingAlgorithm(ListBubbleSortRecursive, lists, "BubbleSortRecursive");

    free(lists);
}

void DoStuffFast(int size)
{
    List** lists = GetThreeLists(size);
    ProcessSortingAlgorithm(ListMergeSort, lists, "MergeSort");

    free(lists);
    lists = GetThreeLists(size);
    ProcessSortingAlgorithm(ListQuickSort, lists, "QuickSort");

    free(lists);
}

void SortAssignment(void (*function)(int))
{
    //1k
    (*function)(1000);
    //10k
    (*function)(10000);
    //100k
    (*function)(100000);
    //1m
    (*function)(1000000);
    //10m
    (*function)(10000000);
    printf("\n");
}

