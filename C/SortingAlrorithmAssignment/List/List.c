#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

List* ListConstructor()
{
    List* toReturn = malloc(sizeof(List));
    toReturn -> CurrentSize = 0;
    toReturn -> Count = 0;
    toReturn -> Array = NULL;

    return toReturn;
}

void ListAppend(List* array, int value)
{
    if(array -> Count == array -> CurrentSize)
    {
        if(array -> Array != NULL)
        {
            array -> CurrentMemorySize <<= 1;
            array -> CurrentSize <<= 1;
            array -> Array = realloc(array -> Array, array -> CurrentMemorySize);
        }
        else
        {
            array -> Array = malloc(sizeof(int));
            array -> CurrentMemorySize = sizeof(int);
            array -> CurrentSize = 1;
        }
    }

    array -> Array[array -> Count] = value;
    array -> Count += 1;
}

void ListPrintElements(List* list)
{
    for(int i = 0; i < list -> Count; i++)
    {
        printf("Element %d: %d\n", i, list -> Array[i]);
    }
}

bool ListContains(List* list, int num)
{
    for (int i = 0; i < list -> Count; i++)
    {
        if(list -> Array[i] == num)
        {
            return true;
        }
    }

    return false;
}

void ListBubbleSort(List* list)
{
    int buffer, i, j;
    for (i = 0; i < list -> Count - 1; i++)
    {
        for (j = 0; j < list -> Count; j++)
        {
            if (list -> Array[j] > list -> Array[j + 1])
            {
                buffer = list -> Array[j + 1];
                list -> Array[j + 1] = list -> Array[j];
                list -> Array[j] = buffer;
            }
        }
    }
}

void ListBubbleSortDescending(List* list)
{
    int buffer, i, j;
    for (i = 0; i < list -> Count - 1; i++)
    {
        for (j = 0; j < list -> Count - i - 1; j++)
        {
            if (list -> Array[j] < list -> Array[j + 1])
            {
                buffer = list -> Array[j + 1];
                list -> Array[j + 1] = list -> Array[j];
                list -> Array[j] = buffer;
            }
        }
    }
}

void AuxiliarListBubbleSortRecursive(List* list, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        if (list -> Array[i] > list -> Array[i + 1])
        {
            int buffer = list -> Array[i];
            list -> Array[i] = list -> Array[i + 1];
            list -> Array[i + 1] = buffer;
        }
    }

    if (count - 1 > 1)
    {
        AuxiliarListBubbleSortRecursive(list, count - 1);
    }
}

void ListBubbleSortRecursive(List* list)
{
    AuxiliarListBubbleSortRecursive(list, list -> Count);
}

int ListIndexOf(List* list, int num)
{
    for (int i = 0; i < list -> Count; i++)
    {
        if(list -> Array[i] == num)
        {
            return i;
        }
    }
    return -1;
}

void ListDebug(List* array)
{
    printf("Current Size: %ld\n", array -> CurrentSize);
    printf("Current Count: %ld\n", array -> Count);
    printf("Current Space in Memory: %ld\n", array -> CurrentMemorySize);
    for(int i = 0; i < array -> Count; i++)
    {
        printf("Value %d: %d\n", i, array -> Array[i]);
    }
}

void merge(int* array, int leftSide, int middlePoint, int rightSide)
{
    int i, j, k;
    int n1 = middlePoint - leftSide + 1;
    int n2 = rightSide - middlePoint;

    int leftArray[n1], rightArray[n2];

    for (i = 0; i < n1; i++)
    {
        leftArray[i] = array[leftSide + i];
    }
    for (j = 0; j < n2; j++)
    {
        rightArray[j] = array[middlePoint + 1 + j];
    }

    i = 0;
    j = 0;
    k = leftSide;
    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
        {
            array[k] = leftArray[i];
            i++;
        }
        else
        {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

void AuxiliarMergeSort(int* array, int leftSide, int rightSide)
{
    if (leftSide < rightSide)
    {
        int middlePoint = (leftSide + rightSide) / 2;

        AuxiliarMergeSort(array, leftSide, middlePoint);
        AuxiliarMergeSort(array, middlePoint + 1, rightSide);

        merge(array, leftSide, middlePoint, rightSide);
    }
}

void ListMergeSort(List* l)
{
    AuxiliarMergeSort(l -> Array, 0, l -> Count);
}

void AuxiliarQuickSortSwap(int *num1, int *num2)
{
    int buffer = *num1;
    *num1 = *num2;
    *num2 = buffer;
}

int AuxiliarQuickSortPartition(int* array, int low, int high)
{
    int pivot = array[high], j = (low - 1);
    for (int i = low; i < high; i++)
    {
        if (array[i] <= pivot)
        {
            j++;
            AuxiliarQuickSortSwap(&array[j], &array[i]);
        }
    }
    AuxiliarQuickSortSwap(&array[j + 1], &array[high]);

    return j + 1;
}

void AuxiliarListQuickSort(int* array, int low, int high)
{
    if (low < high)
    {
        int part = AuxiliarQuickSortPartition(array, low, high);
        AuxiliarListQuickSort(array, low, part - 1);
        AuxiliarListQuickSort(array, part + 1, high);
    }
}

void ListQuickSort(List* l)
{
    AuxiliarListQuickSort(l -> Array, 0, l -> Count - 1);
}