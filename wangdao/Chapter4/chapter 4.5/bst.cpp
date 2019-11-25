#include "pch.h"

#include <stack>
#include <iostream>
#include <functional>

template <typename T>
class Node
{
	typedef T ElemType;

public:
	Node(ElemType data, Node<T>* lchild, Node<T>* rchild)
		: data_(data), lchild_(lchild), rchild_(rchild)
	{

	}

	void set_data(ElemType data) { data_ = data; }
	void set_lchild(Node<T>* lchild) { lchild_ = lchild; }
	void set_rchild(Node<T>* rchild) { rchild_ = rchild; }

	ElemType get_data() const { return data_; }
	Node<T>*& get_lchild() { return lchild_; }
	Node<T>*& get_rchild() { return rchild_; }

private:
	ElemType data_;
	Node<T>* lchild_;
	Node<T>* rchild_;
};

// 中序遍历 BST 非递归
template <typename T>
void InOrder(Node<T>* root);

// 中序遍历 BST Morris Traverse
template <typename T>
void InOrderV2(Node<T>* root);

// 二叉树排序的查找
template <typename T>
Node<T>* Search(Node<T>* root, T key, Node<T>* &parent);

// 二叉排序树的插入 | 递归
template <typename T>
bool Insert(Node<T>* &root, T key);

// 二叉排序树的构建
template<typename T>
void CreateAtree(/*Node<T>* root*/ char str[], int n);

// 二叉排序树的删除
template <typename T>
void DeleteAnode(Node<T>* root, Node<T>* node);

int main()
{
	// constructor a tree
	Node<int> node3{ 3, nullptr, nullptr };
	Node<int> node4{ 4, &node3, nullptr };
	Node<int> node1{ 1, nullptr, nullptr };
	Node<int> node2{ 2, &node1, &node4 };
	Node<int> node8{ 8, nullptr, nullptr };
	// Node<int> node6{ 6, &node2, &node8 };
	Node<int> * node6 = new Node<int>(6,&node2,&node8);


	// InOrder(&node6);
	InOrderV2(node6);
	std::cout << std::endl;

	// Node<int>* parent = nullptr;
	// Node<int>* node = Search(&node6, 8, parent);
	// Node<int>* node = Search(&node6, 8, parent);

	// if (node)
	// {
	//	 std::cout << node->get_data() << std::endl;
	// }

	// if (parent)
	// {
	// 	 std::cout << parent->get_data() << std::endl;
	// }

	// std::cout << std::boolalpha << Insert<int>(node6, 4) << std::endl;
	// InOrderV2(node6);
	// std::cout << std::endl;

	// std::cout << std::boolalpha << Insert<int>(node6, 7) << std::endl;
	// InOrderV2(node6);
	// std::cout << std::endl;

	char str[] = "123468";
	CreateAtree<char>(str, 6);
}

template <typename T>
void InOrder(Node<T>* root)
{
	std::stack<Node<T>*> stk;
	// stk.push(root);

	while (!stk.empty() || root)
	{
		if (root)
		{
			stk.push(root);
			root = root->get_lchild();
		}
		else
		{
			root = stk.top();
			stk.pop();
			std::cout << root->get_data() << ' ';
			root = root->get_rchild();
		}
	}
}

template <typename T>
void InOrderV2(Node<T>* root)
{
	Node<T>* cur = root;
	Node<T>* prev = nullptr;

	while (cur)
	{
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
				std::cout << cur->get_data() << ' ';
				cur = cur->get_rchild();
			}
			else
			{
				prev->set_rchild(cur);
				cur = cur->get_lchild();
			}
		}
		else
		{
			std::cout << cur->get_data() << ' ';
			cur = cur->get_rchild();
		}
	}
}

template <typename T>
Node<T>* Search(Node<T>* root, T key, Node<T>* &parent)
{
	if (root == nullptr)
		return nullptr;

	while (root && root->get_data() != key)
	{
		parent = root;
		if (root->get_data() > key)
			root = root->get_lchild();
		else
			root = root->get_rchild();
	}

	return root;
}

template <typename T>
bool Insert(Node<T>* &root, T key)
{
	if (root == nullptr)
	{
		root = new Node<T>(key, nullptr, nullptr);
		root->set_data(key);
		return true;
	}

	if (root->get_data() == key)
	{
		return false;
	}
	else if (root->get_data() > key)
	{
		Insert(root->get_lchild(), key);
	}
	else
	{
		Insert(root->get_rchild(), key);
	}
}

template<typename T>
void CreateAtree(/*Node<T>* root, */char str[], int n)
{
	Node<T>* root = nullptr;

	for (int i = 0; i < n; ++i)
	{
		Insert(root, str[i]);
	}

	InOrder(root);
}

template <typename T>
void DeleteAnode(Node<T>* root, Node<T>* node)
{
	if (root == nullptr)
		return;

	Node<T>* parent = nullptr;
	if (Search(root, node->get_data(), parent) == nullptr)
	{
		return;
	}

	if (parent == nullptr)
		del(node);
	else if (parent->get_lchild() && parent->get_lchild()->get_data() == node->get_data())
		parent->set_lchild(del(node));
	else
		parent->set_lchild(del(node));
}

template <typename T>
Node<T>* del(Node<T>* node)
{
	if (node->get_lchild() == nullptr && node->get_rchild() == nullptr)
	{
		return nullptr;
	}
	else if (node->get_lchild() == nullptr || node->get_rchild() == nullptr)
	{
		return node->get_lchild() ? node->get_lchild() : node->get_rchild();
	}
	
	Node<T>* pre = node, *cur = node->get_rchild();
	while (cur->get_lchild())
	{
		pre = cur;
		cur = cur->get_lchild();
	}

	node->get_data() = cur->get_data();
	// (pre == node ? node->get_rchild() : pre->get_lchild()) = cur->get_rchild();
	if (pre == node)
	{
		pre->set_rchild(cur->get_rchild());
	}
	else
	{
		pre->set_lchild(cur->get_rchild());
	}

	return node;
}