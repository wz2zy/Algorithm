// 王道真垃圾 我还要去考浙大的研究生 真的讽刺
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

// 二叉树相似
template <typename T>
bool IsSimilarTree(Node<T>* root1, Node<T>* root2);

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

	Node<char> nodeg1{ 'G', nullptr, nullptr };
	Node<char> nodeh1{ 'H', nullptr, nullptr };
	Node<char> nodej1{ 'J', nullptr, nullptr };
	// Node<char> nodei1{ 'I', nullptr, &nodej1 };
	Node<char> nodei1{ 'I', nullptr, nullptr };
	Node<char> noded1{ 'D', &nodeg1, &nodeh1 };
	Node<char> nodee1{ 'E', nullptr, nullptr };
	Node<char> nodeb1{ 'B', &noded1, &nodee1 };
	Node<char> nodef1{ 'F', &nodei1, nullptr };
	Node<char> nodek1{ 'K', nullptr, nullptr };
	Node<char> nodec1{ 'C', &nodek1, &nodef1 };
	Node<char> nodea1{ 'A', &nodeb1, &nodec1 };

	std::cout << std::boolalpha << IsSimilarTree(&nodea1, &nodea) << std::endl;

	system("pause...");
}

template <typename T>
bool IsSimilarTree(Node<T>* root1, Node<T>* root2)
{
	if (root1 == nullptr && root2 == nullptr)
		return true;
	else if (root1 == nullptr || root2 == nullptr)
		return false;
	else {
		bool lefts = IsSimilarTree(root1->get_lchild(), root2->get_lchild());
		bool rights = IsSimilarTree(root1->get_rchild(), root2->get_rchild());
		return lefts && rights;
	}
}

template <typename T>
void LinkAllNode(Node<T>* node)
{
	Node<T>* head = nullptr;
	Node<T>* preleaf = nullptr;
	Node<T>* pre = nullptr;
	std::stack<Node<T>*> stk;
	stk.push(node);
	
	while (!stk.empty() || node)
	{
		if (node)
		{
			while (node->get_lchild())
			{
				stk.push(node->get_lchild());
				node = node->get_lchild();
			}

			node = node->get_rchild();
		}
		else
		{
			node = stk.top();
			if (node->get_rchild() && node->get_rchild() != pre)
			{
				stk.push(node->get_rchild());
				node = node->get_rchild();
			}
			else
			{
				if (node->get_rchild() == nullptr && node->get_lchild() == nullptr)
				{
					if (preleaf == nullptr)
					{
						preleaf = node;
						head = preleaf;
					}
					else
					{
						preleaf->set_rchild(node);
						preleaf = node;
					}
				}

				stk.pop();
				// std::cout << node->get_data() << ' ';
				pre = node;
				node = nullptr;
			}
		}
	}

	do
	{
		std::cout << head->get_data() << ' ';
		head = head->get_rchild();
	} while (head != nullptr);

	std::cout << std::endl;
}