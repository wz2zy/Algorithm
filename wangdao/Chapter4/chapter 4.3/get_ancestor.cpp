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

// 打印某节点的祖先
template <typename T>
void get_ancestor(Node<T>* node, const T& x);

// 层次遍历
template <typename T>
void leveltraverse(Node<T>* node);

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

	get_ancestor(&nodea, 'J');
	// leveltraverse(&nodea);

	system("pause...");
}

template <typename T>
void get_ancestor(Node<T>* node, const T& x)
{
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
				stk.pop();
				if (node->get_data() == x)
					break;

				// std::cout << node->get_data() << ' ';
				pre = node;
				node = nullptr;
			}
		}
	}

	while (!stk.empty())
	{
		node = stk.top();
		stk.pop();
		std::cout << node->get_data() << ' ';
	}

	std::cout << std::endl;
}

template <typename T>
void leveltraverse(Node<T>* node)
{
	std::queue<Node<T>*> que;
	que.push(node);

	while (!que.empty())
	{
		node = que.front();
		que.pop();
		std::cout << node->get_data() << ' ';

		if (node->get_lchild())
		{
			que.push(node->get_lchild());
		}
		if (node->get_rchild())
		{
			que.push(node->get_rchild());
		}
	}
}