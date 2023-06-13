#ifndef MAXHEAP
#define MAXHEAP

#include "Heap.cpp"

class MinHeap : public Heap
{
	void AdjustGoingUp(int64_t position) override
	{
		if(position == -1)
		{
			return;
		}
		
		int64_t ownerIndex = OwnerIndex(position);
		if(ownerIndex == -1)
		{
			return;
		}
		
		if(Data[position] > Data[ownerIndex])
		{
			Swap(Data[position], Data[ownerIndex]);
			AdjustGoingUp(ownerIndex);
		}
	}
	
	void AdjustGoingDown(int64_t position) override
	{
		if(position == -1 || LeftSonIndex(position) == -1)
		{
			return;
		}
		
		int64_t greatestSonIndex;
		{
			int64_t leftSonIndex = LeftSonIndex(position);
			int64_t rightSonIndex = RightSonIndex(position);
			greatestSonIndex = rightSonIndex == -1 || Data[leftSonIndex] > Data[rightSonIndex] ? leftSonIndex : rightSonIndex;
		}
		
		if(Data[greatestSonIndex] > Data[position])
		{
			Swap(Data[position], Data[greatestSonIndex]);
			AdjustGoingDown(greatestSonIndex);
		}
	}
};

#endif