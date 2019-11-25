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

/* 递归求树的深度 */
template <typename T>
size_t get_treedepthrec(Node<T>* node);

/* 非递归求树的深度 */
template <typename T>
size_t get_treedepth(Node<T>* node);

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

	std::cout << "height = " << get_treedepth(&nodea) << std::endl;
	std::cout << "height = " << get_treedepthrec(&nodea) << std::endl;

	system("pause...");
}

template <typename T>
size_t get_treedepthrec(Node<T>* node)
{
	// 递归求树的深度
	if (node == nullptr)
		return 0;

	size_t ldepth = get_treedepth(node->get_lchild());
	size_t rdepth = get_treedepth(node->get_rchild());

	return (ldepth > rdepth ? ldepth : rdepth) + 1;
}

template <typename T>
size_t get_treedepth(Node<T>* node)
{
	// 利用层次遍历求深度

	std::size_t depth = 0;
	std::queue<Node<T>*> que;
	que.push(node);

	while (!que.empty())
	{
		size_t count = que.size();
		for (size_t sz = 0; sz < count; ++sz)
		{
			node = que.front();
			que.pop(); 
			
			if (node->get_lchild())
				que.push(node->get_lchild());
			if (node->get_rchild())
				que.push(node->get_rchild());
		}


		++depth;
	}

	return depth;
}