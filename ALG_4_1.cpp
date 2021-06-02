#include "RBTree.h"

using namespace std;

int main()
{
	RBtree tree;
	tree.insert(45, 'F');
	tree.insert(55, 'A');
	tree.insert(70, 'G');
	tree.insert(20, 'C');
	tree.insert(30, 'B');
	tree.insert(10, 'D');
	tree.insert(25, 'E');
	tree.insert(500, 'H');
	tree.get_values();
	tree.remove(500);
	tree.print();
}