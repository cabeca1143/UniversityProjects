#include "Functions/Functions.h"

int main()
{
    //Separei os BubbleSorts do MergeSort e QuickSort porque eles são extremamente lentos
    SortAssignment(DoStuffFast);
    SortAssignment(DoStuffSlow);
    return 0;
}