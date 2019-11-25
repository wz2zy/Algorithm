#include "pch.h"

#include <stack>
#include <queue>
#include <iostream>

template <typename T>
struct Node
{
	typedef T ElemType;

	Node<T>* childptr;
	Node<T>* sibling;
	ElemType data;
};

// 题目要求: 已知一棵树的层次序列以及每个结点的度,构建此树的孩子 兄弟链表
template <typename T>
Node<T>* constructatree(char levelorder[], unsigned short degree[], unsigned short len1, unsigned short len2);

int main(void)
{
	unsigned int leaves = 0;
	Node<char>* root;

	Node<char> nodec{ nullptr, nullptr, 'C' };
	Node<char> nodea{ nullptr, nullptr, 'A' };
	Node<char> nodeu{ &nodea, nullptr, 'U' };
	Node<char> nodeq{ &nodec, &nodeu, 'Q' };
	Node<char> nodel{ nullptr, nullptr, 'L' };
	Node<char> nodeg{ &nodel, nullptr, 'G' };
	Node<char> nodee{ nullptr, &nodeg, 'E' };
	Node<char> nodes{ &nodeq, &nodee, 'S' };
	Node<char> noded{ &nodes, nullptr, 'D' };

	return 0;
}

// 我感觉到了应该这么做，但是没有理清楚这个关系，逻辑能力有待加强
template <typename T>
Node<T>* constructatree(char levelorder[], unsigned short degree[], unsigned short length)
{
	if (length == 0)
		return;

	// 先集中生成结点
	Node<T>* Nodes = new Node<T>[length];
	for (unsigned short len = 0; len < length; ++len)
	{
		Nodes[len]->data = levelorder[len];
		Nodes[len]->child = Nodes[len]->sibling = nullptr;
	}

	for (unsigned short len = 0; len < length; ++len)
	{
		unsigned short dg = degree[len];
		if (dg)
		{
			++k;
			Nodes[len]->child = levelorder[k];
			
			for (int i = 1; i < dg; ++i)
			{
				++k;
				Nodes[k - 1]->child = Nodes[k];
			}
		}
	}
}