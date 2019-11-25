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

// 删除以 x 为节点的子树
/* 递归 */
template <typename T>
void deletethexsubtree(Node<T>* root, const T& x);

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

	SearchNode(&nodea, 'C');
	leveltraverse(&nodea);

	system("pause...");
}

template <typename T>
void SearchNode(Node<T>* root, const T& x)
{
	if (root == nullptr)
		return;
	
	if (root->get_data() == x)
	{
		deletethexsubtree(x);
		return;
	}

	std::queue<Node<T>*> que;
	que.push(root);

	while (!que.empty())
	{
		root = que.front();
		que.pop();

		if (root->get_lchild())
		{
			if (root->get_lchild()->get_data() == x)
			{
				deletethexsubtree(root->get_lchild());
				root->set_lchild(nullptr); // 删除一个结点不要忘了将其父节点的指针修改
			}
			else
			{
				que.push(root->get_lchild());
			}
		}
		
		if (root->get_rchild())
		{
			if (root->get_rchild()->get_data() == x)
			{
				deletethexsubtree(root->get_rchild());
				root->set_rchild(nullptr);
			}
			else
			{
				que.push(root->get_rchild());
			}
		}
	}
}

template <typename T>
void deletethexsubtree(Node<T>* root)
{
	if (root == nullptr)
		return;

	deletethesubtree(root->get_lchild());
	deletethesubtree(root->get_rchild());
	delete root;
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