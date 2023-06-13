#ifndef HEAP
#define HEAP

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Heap
{
	vector<int32_t> Data;
	
	[[nodiscard]] int64_t LeftSonIndex(int64_t index) const
	{
		return GetSonIndex(index, SonType::Left);
	}
	
	[[nodiscard]] int64_t RightSonIndex(int64_t index) const
	{
		return GetSonIndex(index, SonType::Right);
	}
	
	[[nodiscard]] int64_t OwnerIndex(int64_t index) const
	{
		if(index <= 0 || index >= Data.size())
		{
			return -1;
		}
		return floor(--index/2);
	}
	
	void Push(int32_t value)
	{
		Data.push_back(value);
		AdjustGoingUp((int64_t)Data.size() - 1);
	}
	
	int32_t Pop()
	{
		if(Data.empty())
		{
			return -1;
		}
		
		int32_t toReturn = Data.front();
		Data.front() = Data.back();
		Data.pop_back();
		AdjustGoingDown(0);
		return toReturn;
	}
	
	void PrintAll()
	{
		for(int32_t num : Data)
		{
			cout << num << " ";
		}
		cout << endl;
	}

private:
	enum SonType : short
	{
		Left = 1,
		Right = 2
	};
	
	[[nodiscard]] int64_t GetSonIndex(int64_t index, SonType type) const
	{
		if (index >= Data.size())
		{
			return -1;
		}
		index = index * 2 + type;
		if (index >= Data.size())
		{
			return -1;
		}
		return index;
	}
	
	virtual void AdjustGoingUp(int64_t position) = 0;
	
	virtual void AdjustGoingDown(int64_t position) = 0;

protected:
	static void Swap(int32_t& num1, int32_t& num2)
	{
		int32_t buffer = num1;
		num1 = num2;
		num2 = buffer;
	}
};

#endif