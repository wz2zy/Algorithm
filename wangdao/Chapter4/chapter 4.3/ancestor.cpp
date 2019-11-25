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

// 打印某节点的祖先
template <typename T>
void get_ancestor(Node<T>* root, Node<T>* node1, Node<T>* node2);

// DFS 的到根结点到某个结点的路径
template <typename T>
void pathtonode(Node<T>* root, Node<T>* node, std::vector<Node<T>*>& path);

// 打印某节点的祖先
template <typename T>
bool lca(Node<T>* root, Node<T>* node1, Node<T>* node2, Node<T>* res);

template <typename T>
void pathtonodeV2(Node<T>* root, Node<T>* node1, Node<T>* node2);

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

	std::vector<Node<char>*> path;
	// get_ancestor(&nodea, &nodeg, &nodee);
	// leveltraverse(&nodea);
	// pathtonode(&nodea, &nodee, path);
	// pathtonode(&nodea, &nodee, path);
	pathtonodeV2(&nodea, &nodeg, &nodeh);

	system("pause...");
}

template <typename T>
void get_ancestor(Node<T>* root, Node<T>* node1, Node<T>* node2)
{
	std::vector<Node<T>*> path1;
	std::vector<Node<T>*> path2;

	pathtonode(root, node1, path1);
	pathtonode(root, node2, path2);

	Node<T>* ancestor = root;
	auto iter1 = path1.begin();
	auto iter2 = path2.begin();

	if (path1.size() > path2.size())
	{
		std::advance(iter1, path1.size() - path2.size());
	}
	else
	{
		std::advance(iter2, path2.size() - path1.size());
	}

	while (*iter2 != *iter1)
	{
		++iter1;
		++iter2;
	}

	// std::cout << *iter1->get_data() << std::endl;
	// std::cout << iter1->get_data() << std::endl;
}

template <typename T>
void pathtonode(Node<T>* root, Node<T>* node, std::vector<Node<T>*>& path)
{
	if (root == nullptr)
		return;

	Node<T>* pre = nullptr;
	std::stack<Node<T>*> stk;
	stk.push(root);

	while (!stk.empty() || root)
	{
		if (root)
		{
			while (root->get_lchild())
			{
				stk.push(root->get_lchild());
				root = root->get_lchild();
			}

			root = root->get_rchild();
		}
		else
		{
			root = stk.top();
		
			if (root->get_rchild() && root->get_rchild() != pre)
			{
				stk.push(root->get_rchild());
				root = root->get_rchild();
			}
			else
			{
				// std::cout << root->get_data() << ' ';
				if (root == node)
					break;

				stk.pop();
				pre = root;
				root = nullptr;
			}
		}
	}

	while (!stk.empty())
	{
		path.push_back(stk.top());
		stk.pop();
		// std::cout << node->get_data() << ' ';
	}
}

template <typename T>
void pathtonodeV2(Node<T>* root, Node<T>* node1, Node<T>* node2)
{
	if (root == nullptr)
		return;

	Node<T>* pre = nullptr;
	std::stack<Node<T>*> stk, stk1;
	stk.push(root);

	while (!stk.empty() || root)
	{
		if (root)
		{
			while (root->get_lchild())
			{
				stk.push(root->get_lchild());
				root = root->get_lchild();
			}

			root = root->get_rchild();
		}
		else
		{
			root = stk.top();

			if (root->get_rchild() && root->get_rchild() != pre)
			{
				stk.push(root->get_rchild());
				root = root->get_rchild();
			}
			else
			{
				// std::cout << root->get_data() << ' ';
				if (root == node1 || root == node2)
				{
					if (stk1.empty())
					{
						stk1 = stk;
					}
					else
					{
						break;
					}
				}

				stk.pop();
				if (!stk1.empty() && stk1.top() == root)
				{
					stk1.pop();
				}

				pre = root;
				root = nullptr;
			}
		}
	}

	while (!stk1.empty())
	{
		node1 = stk1.top();
		stk.pop();
		std::cout << node1->get_data() << ' ';
	}
}
