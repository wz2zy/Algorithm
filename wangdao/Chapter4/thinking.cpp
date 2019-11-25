#include "pch.h"

#include <stack>
#include <queue>
#include <vector>
#include <iterator>
#include <iostream>

template <typename T>
class Node
{
	typedef T ElemType;

public:
	Node(ElemType data, Node<ElemType>* lchild = nullptr, Node<ElemType>* rchild = nullptr)
		: data_(data), lchild_(lchild), rchild_(rchild)
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

template <typename T>
void JudgeConstructCorrect(Node<T>* root);

template <typename T>
void PreOrder(Node<T>* root);

template <typename T>
void InOrder(Node<T>* root);

template <typename T>
void PrintAllSuitablePath(Node<T>* root, std::vector<T>& path, T current_sum, T expect_sum);

int main()
{
	// construtcor a tree
	Node<int> node4{ 4, nullptr, nullptr };
	Node<int> node7{ 7, nullptr, nullptr };	
	Node<int> node12{ 12, nullptr, nullptr };
	Node<int> node5{ 5, &node4, &node7 };
	Node<int> node10{ 10, &node5, &node12 };

	// judge construct correct
	// JudgeConstructCorrect(&node10);

	// print all the path sum = data
	std::vector<int> path;
	PrintAllSuitablePath(&node10, path, 0, 22);
}

template <typename T>
void JudgeConstructCorrect(Node<T>* root)
{
	PreOrder(root);
	std::cout << std::endl;
	InOrder(root);
	std::cout << std::endl;
}

template <typename T>
void PreOrder(Node<T>* root)
{
	if (root)
	{
		std::cout << root->get_data() << ' ';
		PreOrder(root->get_lchild());
		PreOrder(root->get_rchild());
	}
}

template <typename T>
void InOrder(Node<T>* root)
{
	if (root)
	{
		InOrder(root->get_lchild());
		std::cout << root->get_data() << ' ';
		InOrder(root->get_rchild());
	}
}

template <typename T>
void PrintAllSuitablePath(Node<T>* root, std::vector<T>& path, T current_sum, T expect_sum)
{
	if (root == nullptr)
	{
		return;
	}

	current_sum += root->get_data();
	path.push_back(root->get_data());
	bool is_leaf = (!root->get_lchild()) && (!root->get_rchild());
	if (is_leaf && (current_sum == expect_sum))
	{
		typename std::vector<T>::const_iterator iter;
		for (iter = path.cbegin(); iter != path.cend(); ++iter)
			std::cout << *iter << ' ';
		std::cout << std::endl;
	}

	PrintAllSuitablePath(root->get_lchild(), path, current_sum, expect_sum);
	PrintAllSuitablePath(root->get_rchild(), path, current_sum, expect_sum);
	path.pop_back();
}