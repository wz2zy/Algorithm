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

// 后序遍历
template <typename T>
void PostOrderV1(Node<T>* node);

template <typename T>
void PostOrderV2(Node<T>* node);

template <typename T>
void PostOrderV3(Node<T>* node);

template <typename T>
void printReverse(Node<T>* from, Node<T>* to);

template <typename T>
void Reverse(Node<T>* from, Node<T>* to);

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

	PostOrderV1(&nodea);
	std::cout << std::endl;

	PostOrderV2(&nodea);

	PostOrderV3(&nodea);

	system("pause...");
}

template <typename T>
void PostOrderV1(Node<T>* node)
{
	Node<T>* pre = nullptr;
	std::stack<Node<T>*> stk;

	while (!stk.empty() || node)
	{
		if (node)
		{
			stk.push(node);
			node = node->get_lchild();
		}
		else
		{
			node = stk.top();
			if (node->get_rchild() && node->get_rchild() != pre)
			{
				node = node->get_rchild();
			}
			else
			{
				std::cout << node->get_data() << ' ';
				stk.pop();
				pre = node;
				node = nullptr;
			}
		}
	}
}

template <typename T>
void PostOrderV2(Node<T>* node)
{
	std::vector<T> res;
	std::stack<Node<T>*> stk;
	stk.push(node);

	while (!stk.empty())
	{
		node = stk.top();
		stk.pop();
		res.insert(std::begin(res), node->get_data());

		if (node->get_lchild())
			stk.push(node->get_lchild());
		if (node->get_rchild())
			stk.push(node->get_rchild());
	}

	std::copy(std::cbegin(res), std::cend(res), std::ostream_iterator<T>(std::cout, " "));
	std::cout << std::endl;
}

template <typename T>
void PostOrderV3(Node<T>* node)
{
	Node<T> supNode{'$', node};
	
	Node<T>* cur = &supNode;
	Node<T>* pre = nullptr;
	while (cur)
	{
		if (cur->get_lchild() == nullptr)
		{
			cur = cur->get_rchild();
		}
		else
		{
			pre = cur->get_lchild();
			while (pre->get_rchild() && pre->get_rchild() != cur)
			{
				pre = pre->get_rchild();
			}

			if (pre->get_rchild())
			{
				printReverse(cur->get_lchild(), pre);
				pre->set_rchild(nullptr);
				cur = cur->get_rchild();
			}
			else
			{
				pre->set_rchild(cur);
				cur = cur->get_lchild();
			}
		}
	}
}

template <typename T>
void Reverse(Node<T>* from, Node<T>* to)
{
	Node<T>* pre = from;
	Node<T>* cur = pre->get_rchild();
	Node<T>* prev = nullptr;

	while (pre != to)
	{
		prev = cur->get_rchild();
		cur->set_rchild(pre);
		pre = cur;
		cur = prev;
	}
}

template <typename T>
void printReverse(Node<T>* from, Node<T>* to)
{
	Reverse(from, to);

	Node<T>* node = to;
	while (true)
	{
		std::cout << node->get_data() << ' ';

		if (node == from)
			break;

		node = node->get_rchild();
	}

	Reverse(to, from);
}