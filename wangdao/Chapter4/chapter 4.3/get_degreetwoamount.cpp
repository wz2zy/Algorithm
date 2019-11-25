﻿/*
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

/* 计算所有分支为 2 的结点数量 */
template <typename T>
size_t get_degreetwoamount(Node<T>* root);

/* 递归版本 */
template <typename T>
size_t get_degreetwoamount2(Node<T>* root);

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

	std::cout << "amount = " << get_degreetwoamount2(&nodea) << std::endl;

	system("pause...");
}

template <typename T>
size_t get_degreetwoamount(Node<T>* root)
{
	size_t amount = 0;
	std::queue<Node<T>*> que;
	que.push(root);

	while (!que.empty())
	{
		root = que.front();
		que.pop();

		if (root->get_lchild() && root->get_rchild())
		{
			std::cout << root->get_data() << std::endl;
			++amount;
		}

		if (root->get_lchild())
			que.push(root->get_lchild());
		if (root->get_rchild())
			que.push(root->get_rchild());
	}

	return amount;
}

template <typename T>
size_t get_degreetwoamount2(Node<T>* root)
{
	if (root == nullptr)
		return 0;
	else if (root->get_lchild() && root->get_rchild())
		return get_degreetwoamount2(root->get_lchild()) + get_degreetwoamount2(root->get_rchild()) + 1;
	else
		return get_degreetwoamount2(root->get_lchild()) + get_degreetwoamount2(root->get_rchild());
}