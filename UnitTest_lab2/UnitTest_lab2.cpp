#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "..\Program2\List.inl"
#include "..\Program2\RB-Tree.inl"
#include "..\Program2\Shannon-Fano.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlab1
{
	TEST_CLASS(RBTreeTest)
	{
	public:
		Tree_Node<int, string> tree;
		TEST_METHOD_INITIALIZE(SetUp)
		{
			tree.Nil_Creating();
			int keys[3] = { 9,10,11 };
			string data[3] = { "nine","ten" ,"eleven" };
			for (size_t i = 0; i < 3; i++)
				tree.Insert(keys[i], data[i]);
		}
		TEST_METHOD(Left_Rotate_Test)
		{
			List<int> temp;
			tree.left_rorate(tree.Get_Root());
			tree.Get_Keys(tree.Get_Root(), &temp);

			Assert::IsTrue(temp.at(0) == 11 && temp.at(1) == 10 && temp.at(2) == 9);
		}

		TEST_METHOD(Right_Rotate_Test)
		{
			List<int> temp;
			tree.right_rorate(tree.Get_Root());
			tree.Get_Keys(tree.Get_Root(), &temp);

			Assert::IsTrue(temp.at(0) == 9 && temp.at(1) == 10 && temp.at(2) == 11);
		}
		TEST_METHOD(Insert_Test_1)
		{
			List<int> temp;
			tree.Insert(25, "hello");
			tree.Get_Keys(tree.Get_Root(), &temp);

			Assert::IsTrue(temp.at(0) == 10 && temp.at(1) == 9 && temp.at(2) == 11 && temp.at(3) == 25);
		}
		TEST_METHOD(Insert_Test_2)
		{
			List<int> temp;
			tree.Insert(-1, "hello");
			tree.Get_Keys(tree.Get_Root(), &temp);

			Assert::IsTrue(temp.at(0) == 10 && temp.at(1) == 9 && temp.at(2) == -1 && temp.at(3) == 11);
		}
		TEST_METHOD(Find_Test_1)
		{
			string correct = "nine";
			Assert::AreEqual(tree.Find(9), correct);
		}
		TEST_METHOD(Find_Test_2)
		{
			try
			{
				Tree_Node<int, int> temp;
				temp.Find(5);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "RB Tree is empty.");
			}
		}
		TEST_METHOD(Find_Test_3)
		{
			try
			{
				tree.Find(5);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Node not found.");
			}
		}
		TEST_METHOD(Remove_Test_1)
		{
			List<int> temp;
			tree.Insert(12, "twelve");
			tree.Insert(13, "thirteen");
			tree.Remove(10);

			tree.Get_Keys(tree.Get_Root(), &temp);

			Assert::IsTrue(temp.at(0) == 11 && temp.at(1) == 9 && temp.at(2) == 12 && temp.at(3) == 13);
		}
		TEST_METHOD(Remove_Test_2)
		{
			try
			{
				Tree_Node<int, int> temp;
				temp.Remove(5);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "RB Tree is empty.");
			}
		}
		TEST_METHOD(Remove_Test_3)
		{
			try
			{
				tree.Remove(5);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Node not found.");
			}
		}
		TEST_METHOD(Clear_Test)
		{
			tree.Clear();
			Assert::IsTrue(tree.Get_Root() == tree.Get_Nil());
		}
		TEST_METHOD(Get_Keys_Test)
		{
			List<int> keys;
			tree.Get_Keys(tree.Get_Root(), &keys);
			Assert::IsTrue(keys.at(0) == 10 && keys.at(1) == 9 && keys.at(2) == 11);
		}
		TEST_METHOD(Get_Values_Test)
		{
			List<string> values;
			tree.Get_Values(tree.Get_Root(), &values);
			Assert::IsTrue(values.at(0) == "ten" && values.at(1) == "nine" && values.at(2) == "eleven");
		}
	};
	TEST_CLASS(LinkedListTest)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			List<int> lst;
			Assert::IsTrue(lst.GetSize() == 0);
		}
		TEST_METHOD(IsEmptyTest1)
		{
			List<int> lst;
			Assert::IsTrue(lst.isEmpty());
		}
		TEST_METHOD(IsEmptyTest2)
		{
			List<int> lst;
			lst.push_back(3);
			Assert::IsTrue(lst.isEmpty() == false);
		}
		TEST_METHOD(AtTest1)
		{
			List<int> lst;
			lst.push_back(3);
			Assert::IsTrue(lst.at(0) == 3);
		}
		TEST_METHOD(AtTest2)
		{
			List<int> lst;
			lst.push_back(3);
			lst.push_front(2);
			Assert::IsTrue(lst.at(0) == 2, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 3, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 2, L"Assert 3");
		}
		TEST_METHOD(AtTest3)
		{
			List<int> lst;
			lst.push_back(3);
			try
			{
				lst.at(-5);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
		TEST_METHOD(GetSizeTest1)
		{
			List<int> lst;
			Assert::IsTrue(lst.GetSize() == 0);
		}
		TEST_METHOD(GetSizeTest2)
		{
			List<int> lst;
			lst.push_back(3);
			lst.push_front(2);
			Assert::IsTrue(lst.GetSize() == 2);
		}
		TEST_METHOD(GetSizeTest3)
		{
			List<int> lst;
			lst.push_back(3);
			lst.push_front(2);
			lst.pop_back();
			lst.pop_front();
			Assert::IsTrue(lst.GetSize() == 0);
		}

		TEST_METHOD(PushBackTest1)
		{
			List<int> lst;
			lst.push_back(3);
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 1");
			Assert::IsTrue(lst.at(0) == 3, L"Assert 2");
		}
		TEST_METHOD(PushBackTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 3, L"Assert 2");
		}
		TEST_METHOD(PushFrontTest1)
		{
			List<int> lst;
			lst.push_front(3);
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 1");
			Assert::IsTrue(lst.at(0) == 3, L"Assert 2");
		}
		TEST_METHOD(PushFrontTest2)
		{
			List<int> lst;
			lst.push_front(0);
			lst.push_front(1);
			lst.push_front(2);
			lst.push_front(3);
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 0, L"Assert 2");
		}
		TEST_METHOD(PopBackTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.pop_back();
			Assert::IsTrue(lst.GetSize() == 3);
		}
		TEST_METHOD(PopBackTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.pop_back();
			Assert::IsTrue(lst.GetSize() == 0);
		}
		TEST_METHOD(PopBackTest3)
		{
			List<int> lst;
			try
			{
				lst.pop_back();
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Linked list is Empty.");
			}
		}
		TEST_METHOD(PopFrontTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.pop_front();
			Assert::IsTrue(lst.at(0) == 1, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 2, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 3, L"Assert 3");
		}
		TEST_METHOD(PopFrontTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.pop_front();
			Assert::IsTrue(lst.isEmpty(), L"Assert 1");
		}
		TEST_METHOD(PopFrontTest3)
		{
			List<int> lst;
			try
			{
				lst.pop_front();
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Linked list is Empty.");
			}
		}
		TEST_METHOD(InsertTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.insert(0, 21);
			Assert::IsTrue(lst.at(0) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 0, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 3");
		}
		TEST_METHOD(InsertTest2)
		{
			List<int> lst;
			lst.insert(0, 21);
			Assert::IsTrue(lst.at(0) == 21, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 2");
		}
		TEST_METHOD(InsertTest3)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.insert(2, 21);
			Assert::IsTrue(lst.at(2) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 2, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 3");
		}
		TEST_METHOD(InsertTest4)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.insert(2, 21);
			Assert::IsTrue(lst.at(2) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 2, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 6, L"Assert 3");
		}
		TEST_METHOD(InsertTest5)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			try
			{
				lst.insert(-3, 21);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
		TEST_METHOD(SetTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.set(0, 21);
			Assert::IsTrue(lst.at(0) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 1, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 3, L"Assert 3");
		}
		TEST_METHOD(SetTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.set(2, 21);
			Assert::IsTrue(lst.at(2) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 3, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 9, L"Assert 3");
		}
		TEST_METHOD(SetTest3)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.set(7, 21);
			Assert::IsTrue(lst.at(7) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(8) == 8, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 9, L"Assert 3");
		}
		TEST_METHOD(SetTest4)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.set(8, 21);
			Assert::IsTrue(lst.at(8) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(7) == 7, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 9, L"Assert 3");
		}
		TEST_METHOD(SetTest5)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			try
			{
				lst.set(-3, 21);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
		TEST_METHOD(RemoveTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.remove(0);
			Assert::IsTrue(lst.at(0) == 1, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 2");
		}
		TEST_METHOD(RemoveTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.remove(2);
			Assert::IsTrue(lst.at(2) == 3, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 8, L"Assert 2");
		}
		TEST_METHOD(RemoveTest3)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.remove(6);
			Assert::IsTrue(lst.at(6) == 7, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 8, L"Assert 2");
		}
		TEST_METHOD(RemoveTest4)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.remove(5);
			Assert::IsTrue(lst.at(4) == 4, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 5, L"Assert 2");
		}
		TEST_METHOD(RemoveTest5)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			try
			{
				lst.remove(-2);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
	};
	TEST_CLASS(FunctionTest)
	{
	public:

		TEST_METHOD(SearchMiddleTest)
		{
			int A[10];
			for (int i = 0; i < 10; i++)
				A[9-i] = i;
			int mid = SearchMiddle(A, 0, 9);
			Assert::IsTrue(mid == 2);
		}
		TEST_METHOD(BubbleSortTest)
		{
			int* A = new int[10];
			char* B = new char[10]{ 'j','i','h','g','f','e', 'd', 'c', 'b', 'a' };
			char* check = new char[10]{'a', 'b' , 'c', 'd','e','f','g','h','i', 'j' };

			for (int i = 0; i < 10; i++)
				A[i] = i;

			BubbleSort(A, B, 10);

			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(A[i] == 9-i);
				Assert::IsTrue(B[i] == check[i]);
			}
		}
		TEST_METHOD(ShannonFanoTest)
		{
			string str = "i can see i can fly";
			string test = "0100 11 101 100 0101 11 0001 011 011 11 0100 11 101 100 0101 11 0011 0010 0000";
			string encoding_result, decoding_result;
			Result(str, encoding_result, decoding_result);
			for (int i = 0; i < encoding_result.length()-1; i++)
			{
				Assert::IsTrue(encoding_result[i] == test[i], L"test1");
			}
			Assert::IsTrue(decoding_result == str,L"test2");
		}
	};
}
