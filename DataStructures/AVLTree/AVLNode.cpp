#ifndef SEARCH_NODE
#define SEARCH_NODE

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct AVLNode
{
    AVLNode* Left = nullptr;
    AVLNode* Right = nullptr;
    int64_t Data = -1;


    explicit AVLNode(const int64_t data)
    {
        Data = data;
    }

    AVLNode* Append(int64_t value)
    {
        if(this == nullptr)
        {
            return new AVLNode(value);
        }

        if(value < Data)
        {
            Left = Left->Append(value);
        }
        else if(value > Data)
        {
            Right = Right->Append(value);
        }
        else
        {
            return this;
        }

        int64_t balance = GetBalance();
        if (balance > 1 && value < Left->Data)
        {
            return RotateRight();
        }

        if (balance < -1 && value > Left->Data)
        {
            return RotateLeft();
        }

        if (balance > 1 && value > Left->Data)
        {
            Left = RotateLeft();
            return RotateRight();
        }

        if (balance < -1 && value < Right->Data)
        {
            Right = RotateRight();
            return RotateLeft();
        }

        /*if(balance > 1)
        {
            if(value < Left->Data)
            {
                return RotateRight();
            }
            else if (value > Left->Data)
            {
                Left = Left->RotateLeft();
                return RotateRight();
            }
        }

        if (balance < -1)
        {
            if (value > Right->Data)
            {
                return RotateLeft();
            }
            else// if (value < Right->Data)
            {
                Right = Right->RotateRight();
                return RotateLeft();
            }
        }*/

        return this;
    }

    void PrintTree()
    {
        if (this != nullptr)
        {
            Left->PrintTree();
            cout << Data << endl;
            Right->PrintTree();
        }
    }

    [[nodiscard]] int64_t GetBalance() const
    {
        return Right->GetHeight() - Left->GetHeight();
    }


    bool Contains(const int64_t value)
    {
        return Find(value) != nullptr;
    }

    AVLNode& Max()
    {
        if (Right != nullptr)
        {
            return Right->Max();
        }

        return *this;
    }

    AVLNode& Min()
    {
        if (Left != nullptr)
        {
            return Left->Min();
        }

        return *this;
    }

    AVLNode* Find(const int64_t value)
    {
        if (this == nullptr || Data == value)
        {
            return this;
        }

        if (value > Data)
        {
            return Right->Find(value);
        }

        return Left->Find(value);
    }

    AVLNode* Remove(const int64_t value)
    {
        return AuxRemove(value);
    }

    AVLNode* RotateRight()
    {
        AVLNode* buffer = Left;
        Left = buffer->Right;
        buffer->Right = this;
        return buffer;
    }

    AVLNode* RotateLeft()
    {
        AVLNode* buffer = Right;
        Right = buffer->Left;
        buffer->Left = this;
        return buffer;
    }

    void PrintGreaterOrEqual(const int64_t value)
    {
        if (this == nullptr)
        {
            return;
        }

        if (Data >= value)
        {
            cout << Data << endl;
            Left->PrintGreaterOrEqual(value);
        }
        Right->PrintGreaterOrEqual(value);
    }

    void PrintLesser(const int64_t value)
    {
        if (this == nullptr)
        {
            return;
        }

        if (Data < value)
        {
            cout << Data << endl;
            Right->PrintLesser(value);
        }
        Left->PrintLesser(value);
    }

    size_t Count()
    {
        return AuxCount() + 1;
    }

    size_t CountAtLevel(const size_t level)
    {
        return AuxCountAtLevel(0, level);
    }

    void PrintLevel(const size_t level)
    {
        AuxPrintLevel(0, level);
    }

    void PrintLevelOfValue(const int64_t value)
    {
        AuxPrintLevel(value, 0);
    }

    void AuxPrintLevelOfValue(int64_t value, size_t currentLevel)
    {
        if(this == nullptr)
        {
            cout << "Value not found!" << endl;
        }

        if(Data == value)
        {
            cout << currentLevel << endl;
            return;
        }

        if(value < Data)
        {
            Left->AuxPrintLevel(value, currentLevel + 1);
            return;
        }
        Right->AuxPrintLevel(value, currentLevel + 1);
    }

    vector<AVLNode*>& GetAllNodes()
    {
        auto* toReturn = new vector<AVLNode*>();
        AuxGetAllNodes(*toReturn);
        return *toReturn;
    }

    void PrintLeafNodes()
    {
        if (this == nullptr)
        {
            return;
        }

        if (IsLeafNode())
        {
            cout << Data << endl;
            return;
        }
        Left->PrintLeafNodes();
        Right->PrintLeafNodes();
    }

    int64_t GetHeight()
    {
        if (this == nullptr)
        {
            return 0;
        }

        return 1 + max(Left->GetHeight(), Right->GetHeight());
    }

    [[nodiscard]] bool IsLeafNode() const
    {
        return Left == nullptr && Right == nullptr;
    }

    static AVLNode* ReadFromFile(const string& path)
    {
        ifstream stream(path);
        AVLNode* toReturn = AuxReader(stream);
        stream.close();
        return toReturn;
    }

    static AVLNode& ReadFromString(const string& str)
    {
        stringstream stream(str);
        AVLNode* toReturn = AuxReader(stream);
        stream.clear();
        return *toReturn;
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

    uint32_t GetMaxWidth()
    {
        uint32_t height = GetHeight();
        uint32_t maxWidth = 0;
        for (int i = 0; i < height; i++)
        {
            uint32_t width = GetWidth(i);
            if (width > maxWidth)
            {
                maxWidth = width;
            }
        }

        return maxWidth;
    }

    uint32_t GetWidth(uint32_t level)
    {
        if (this == nullptr)
        {
            return 0;
        }
        if (level == 1)
        {
            return 1;
        }
        return Left->GetWidth(level - 1) + Right->GetWidth(level - 1);
    }

    bool IsBalanced()
    {
        if (this == nullptr)
        {
            return true;
        }

        int64_t leftHeight = Left->GetHeight();
        int64_t rightHeight = Right->GetHeight();
        int64_t diff = leftHeight > rightHeight ? leftHeight - rightHeight : rightHeight - leftHeight;

        if (diff > 1)
        {
            return false;
        }

        return Left->IsBalanced() && Right->IsBalanced();
    }

    bool IsFull()
    {
        return Count() == pow(2, GetHeight());
    }
private:

    size_t AuxCount()
    {
        return (Left == nullptr ? 0 : Left->AuxCount() + 1) + (Right == nullptr ? 0 : Right->AuxCount() + 1);
    }

    size_t AuxCountAtLevel(const size_t currentLevel, const size_t level)
    {
        if (this == nullptr)
        {
            return 0;
        }

        if (currentLevel == level)
        {
            return 1;
        }

        return Left->AuxCountAtLevel(currentLevel + 1, level) + Right->AuxCountAtLevel(currentLevel + 1, level);
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

    void AuxGetAllNodes(vector<AVLNode*>& nodeVector)
    {
        if (this == nullptr)
        {
            return;
        }

        nodeVector.push_back(this);

        Left->AuxGetAllNodes(nodeVector);
        Right->AuxGetAllNodes(nodeVector);
    }

    AVLNode* AuxAppendValue(int64_t value)
    {
        if (this == nullptr)
        {
            return new AVLNode(value);
        }

        if (Data > value)
        {
            Left = Left->AuxAppendValue(value);
        }
        else
        {
            Right = Right->AuxAppendValue(value);
        }

        return this;
    }

    AVLNode* AuxRemove(int64_t value)
    {
        if (this == nullptr)
        {
            return nullptr;
        }

        if (Data == value)
        {
            AVLNode* buffer = nullptr;

            if (IsLeafNode())
            {
                delete (this);
                return nullptr;
            }
            if(Left == nullptr || Right == nullptr)
            {
                AVLNode *aux;
                if (Left == nullptr)
                {
                    aux = Right;
                }
                else
                {
                    aux = Left;
                }
                delete(this);
                return(aux);
            }
            else
            {
                AVLNode* greatest = Left;
                while (greatest->Right != nullptr)
                {
                    greatest = greatest->Right;
                    Data = greatest->Data;
                    greatest->Data = value;
                    Left = Left->AuxRemove(value);
                }
            };
        }

        if (value < Data)
        {
            Left = Left->AuxRemove(value);
        }
        else
        {
            Right = Right->AuxRemove(value);
        }

        return this;
    }

    static AVLNode* AuxReader(istream& stream)
    {
        AVLNode* toReturn = nullptr;
        int num;
        char character;

        stream >> character;
        stream >> num;

        if (num >= 0)
        {
            toReturn = new AVLNode(num);
            toReturn->Left = AuxReader(stream);
            toReturn->Right = AuxReader(stream);
        }

        stream >> character;
        return toReturn;
    }
};

#endif
