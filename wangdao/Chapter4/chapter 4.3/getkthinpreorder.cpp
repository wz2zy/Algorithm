/*
	后续线索树的遍历不会~，以后会了加上去
*/ 

#include "pch.h"

#include <stack>
#include <queue>
#include <vector>
#include <iterator>
#include <iostream>

#define N 1000

template <typename T>
class Node
{
	typedef T ElemType;

public:
	Node(ElemType data, Node<ElemType>* lchild = nullptr, Node<ElemType>* rchild = nullptr)
		: data_(data), 
		  lchild_(lchild), 
		  rchild_(rchild)
	{

	}

	void set_data(ElemType data) { data_ = data; }
	void set_lchild(Node<ElemType>* lchild) { lchild_ = lchild; }
	void set_rchild(Node<ElemType>* rchild) { rchild_ = rchild; }

	ElemType get_data() const { return data_; }
	Node<ElemType>* get_lchild() const { return lchild_; }
	Node<ElemType>* get_rchild() const { return rchild_; }

private:
	ElemType data_;
	Node<ElemType>* lchild_ = nullptr;
	Node<ElemType>* rchild_ = nullptr;
};

char preOrder[] = "ABDGHECKFIJ";
char inOrder[] = "GDHBEAKCIJF";

// 求先序遍历第 K 个元素
template <typename T>
size_t getktheleminpreorder(Node<T>* root, size_t k);

/* 递归求解第 K 个元素问题 */
template <typename T>
size_t getktheleminpreorderV2(Node<T>* root, size_t k);

int main()
{
	// construtcor a tree
	Node<char> nodeg{ 'G', nullptr, nullptr };
	Node<char> nodeh{ 'H', nullptr, nullptr };
	Node<char> nodej{ 'J', nullptr, nullptr };
	Node<char> nodei{ 'I', nullptr, &nodej };
	Node<char> noded{ 'D', &nodeg, &nodeh };
	Node<char> nodee{ 'E', nullptr, nullptr };
	Node<char> nodeb{ 'B', &noded, &nodee };
	Node<char> nodef{ 'F', &nodei, nullptr };
	Node<char> nodek{ 'K', nullptr, nullptr };
	Node<char> nodec{ 'C', &nodek, &nodef };
	Node<char> nodea{ 'A', &nodeb, &nodec };

	getktheleminpreorder(&nodea, 5);

	system("pause...");
}

template <typename T>
size_t getktheleminpreorder(Node<T>* root, size_t k)
{
	size_t index = 0;
	Node<T>* cur = root;
	Node<T>* prev = nullptr;

	while (cur)
	{

		if (index == k) {
			std::cout << cur->get_data() << std::endl;
			return k;
		}

		if (cur->get_lchild())
		{
			prev = cur->get_lchild();
			while (prev->get_rchild() && prev->get_rchild() != cur)
			{
				prev = prev->get_rchild();
			}

			if (prev->get_rchild())
			{
				prev->set_rchild(nullptr);
				cur = cur->get_rchild();
			}
			else
			{
				if (++index == k) {
					std::cout << cur->get_data() << std::endl;
					return k;
				}

				prev->set_rchild(cur);
				cur = cur->get_lchild();
			}
		}
		else
		{
			if (++index == k) {
				std::cout << cur->get_data() << std::endl;
				return k;
			}

			cur = cur->get_rchild();
		}
	}

	return -1;
}