#include "pch.h"
#include "CppUnitTest.h"
#include "../ALG_4_1/RBTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest41
{
	TEST_CLASS(UnitTest41)
	{
	public:

		TEST_METHOD(insert)
		{
			RBtree T;

			T.insert(50, 'G');
			Assert::AreEqual(T.root->value, 'G');
			T.insert(40, 'F');
			Assert::AreEqual(T.root->left->value, 'F');
			T.insert(70, 'H');
			Assert::AreEqual(T.root->right->value, 'H');
		}
		TEST_METHOD(remove)
		{
			RBtree T;

			T.insert(50, 'G');
			T.insert(40, 'F');
			T.insert(70, 'H');
			T.remove(70);
			Assert::IsNull(T.root->right);
			T.remove(40);
			Assert::IsNull(T.root->left);
			T.remove(50);
			Assert::IsNull(T.root);
		}

		TEST_METHOD(findNode)
		{
			RBtree T;
			T.insert(45, 'F');
			T.insert(55, 'A');
			T.insert(70, 'G');
			T.insert(20, 'C');
			T.insert(30, 'B');
			T.insert(50, 'G');
			Assert::AreEqual(T.findNode(30), true);
		}

		TEST_METHOD(clear)
		{
			RBtree T;
			T.insert(45, 'F');
			T.insert(55, 'A');
			T.insert(70, 'G');
			T.insert(100, 'L');
			T.insert(25, 'M');
			T.insert(58, 'N');
			T.insert(20, 'C');
			T.insert(30, 'B');
			T.insert(50, 'G');
			T.clear();
			Assert::IsNull(T.root);
		}
	};
}
