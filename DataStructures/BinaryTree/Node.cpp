#ifndef NODE
#define NODE

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	Node* Left = nullptr;
	Node* Right = nullptr;
	int64_t Data;

	Node(int64_t data)
	{
		Data = data;
	}

	void OrganizeToBST()
	{
		auto& nodes = GetAllNodes();
		nodes.erase(nodes.begin());
		ClearChilds();

		for (Node* node : nodes)
		{
			node->ClearChilds();
			AppendBST(*node);
		}
	}

	void AppendBST(Node& node)
	{
		if (node.Data < Data)
		{
			if (Left == nullptr)
			{
				Left = &node;
				return;
			}
			Left->AppendBST(node);
			return;
		}

		if (Right == nullptr)
		{
			Right = &node;
			return;
		}
		Right->AppendBST(node);
	}

	void PrintTree()
	{
		if (this != nullptr)
		{
			cout << Data << endl;
			Left->PrintTree();
			Right->PrintTree();
		}
	}

	bool Contains(size_t value)
	{
		if (this == nullptr)
		{
			return false;
		}
		if (Data == value)
		{
			return true;
		}

		return Left->Contains(value) || Right->Contains(value);
	}

	size_t Count()
	{
		return AuxCount() + 1;
	}

	void DeleteTree()
	{
		if (this != nullptr)
		{
			Left->DeleteTree();
			Right->DeleteTree();
			delete(this);
		}
	}

	size_t GetHeight()
	{
		if (this == nullptr)
		{
			return 0;
		}

		size_t leftHeight = Left->GetHeight();
		size_t rightHeight = Right->GetHeight();
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool IsFull()
	{
		return Count() == pow(2, GetHeight());
	}

	bool IsComplete()
	{
		size_t height = GetHeight();
		return CountAtLevel(height - 1) == pow(2, height - 2);
	}

	bool IsBalanced()
	{
		if (this == nullptr)
		{
			return true;
		}

		size_t leftHeight = Left->GetHeight();
		size_t rightHeight = Right->GetHeight();
		size_t diff = leftHeight > rightHeight ? leftHeight - rightHeight : rightHeight - leftHeight;

		if (diff > 1)
		{
			return false;
		}

		return Left->IsBalanced() && Right->IsBalanced();
	}

	size_t CountAtLevel(size_t level)
	{
		return AuxCountAtLevel(0, level);
	}

	void PrintLevel(size_t level)
	{
		AuxPrintLevel(0, level);
	}

	vector<Node*>& GetAllNodes()
	{
		vector<Node*>* toReturn = new vector<Node*>();
		AuxGetAllNodes(*toReturn);
		return *toReturn;
	}

	void PrintLeafNodes()
	{
		if (this == nullptr)
		{
			return;
		}

		if (Left == nullptr && Right == nullptr)
		{
			cout << Data << endl;
		}
		else
		{
			Left->PrintLeafNodes();
			Right->PrintLeafNodes();
		}
	}

private:
	size_t AuxCount()
	{
		return (Left == nullptr ? 0 : Left->AuxCount() + 1) + (Right == nullptr ? 0 : Right->AuxCount() + 1);
	}

	void AuxPrintLevel(size_t level, size_t desiredLevel)
	{
		if (this == nullptr)
		{
			return;
		}
		if (level < desiredLevel)
		{
			Left->AuxPrintLevel(++level, desiredLevel);
			Right->AuxPrintLevel(level, desiredLevel);
			return;
		}
		cout << Data << endl;
	}

	size_t AuxCountAtLevel(size_t currentLevel, size_t level)
	{
		if (this == nullptr)
		{
			return 0;
		}

		if (currentLevel == level)
		{
			return 1;
		}

		return Left->AuxCountAtLevel(++currentLevel, level) + Right->AuxCountAtLevel(currentLevel, level);
	}

	void AuxGetAllNodes(vector<Node*>& nodeVector)
	{
		if (this == nullptr)
		{
			return;
		}

		nodeVector.push_back(this);

		Left->AuxGetAllNodes(nodeVector);
		Right->AuxGetAllNodes(nodeVector);
	}

	void ClearChilds()
	{
		Left = nullptr;
		Right = nullptr;
	}
};

#endif