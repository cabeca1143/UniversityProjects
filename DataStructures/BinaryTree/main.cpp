//Rafael Belinger Bastos de Araújo
//Feito sozinho
//Não lembro se era para colocar algo mais no cabeçalho

#include <iostream>
#include "Node.cpp"
#include "TreeReader.cpp"

using namespace std;

string BoolToString(bool input);
void TestNode(Node* node);

int main()
{
	//1)
	Node* tree1 = TreeReader::ReadFromString("(30(10(20(-1)(-1))(-1))(50(60(70(-1)(-1))(-1))(40(-1)(-1))))");
	Node* tree2 = TreeReader::ReadFromString("(10(20(50(-1)(-1))(30(-1)(-1)))(40(5(-1)(-1))(90(-1)(-1))))");
	Node* tree3 = TreeReader::ReadFromString("(40(20(38(3(1(-1)(-1))(-1))(37(-1)(-1)))(-1))(30(31(35(-1)(-1))(39(10(36(-1)(-1))(-1))(-1)))(-1)))");

	TestNode(tree1);
	TestNode(tree2);
	TestNode(tree3);

	tree1->DeleteTree();
	tree2->DeleteTree();
	tree3->DeleteTree();

	system("pause");

	return 0;
}

//Input por console
/*int main()
{
	string input;
	cin >> input;

	Node* node = TreeReader::ReadFromString(input);
	TestNode(node);

	node->DeleteTree();

	system("pause");

	return 0;
}*/

void TestNode(Node* node)
{
	//2)
	cout << "Print Tree:" << endl;
	node->PrintTree();
	//3)
	cout << "Contains 20: " << BoolToString(node->Contains(20)) << endl;
	//4)
	cout << "Count: " << node->Count() << endl;
	//5)
	cout << "Leaf Nodes:" << endl;
	node->PrintLeafNodes();
	//6)
	cout << "Is Balanced: " << BoolToString(node->IsBalanced()) << endl;
	//7)
	cout << "Is Full: " << BoolToString(node->IsFull()) << endl;
	//8)
	cout << "Print Level 3:" << endl;
	node->PrintLevel(3);
	cout << endl;
}

string BoolToString(bool input)
{
	return input ? "true" : "false";
}