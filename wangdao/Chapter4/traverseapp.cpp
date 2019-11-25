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

// unsigned short degree = 0;

// 统计二叉树中度为 1 的结点个数
template <typename T>
unsigned short StatDegree1NodeAmount(Node<T>* root);

// 统计二叉树的高度
template <typename T>
unsigned short GetTreeHeight(Node<T>* root);

// 统计二叉树的宽度
template <typename T>
unsigned short GetTreeWidth(Node<T>* root);

// 删除二叉树中所有叶节点
template <typename T>
Node<T>* DeleteAllLeaves(Node<T>* root);

// 先序遍历
template <typename T>
void PreOrder(Node<T>* root);

// 中序遍历
template <typename T>
void InOrder(Node<T>* root);

// 指定结点所在的层次
template <typename T>
unsigned short GetNodeLevel(Node<T>* root, Node<T>* idxNode);

// 指定结点所在层次方法二
template <typename T>
unsigned short GetNodeLevelV2(Node<T>* root, Node<T>* idxNode);

// 求二叉树中最大元素的值
template <typename T>
void GetMaxNodeValue(Node<T>* root, T* max);

// 交换每个二叉树的左右子树
template <typename T>
void SwapLNodeRNode(Node<T>* root);

// 输出一棵二叉树中所有结点的数据值及结点所在的层次
template <typename T>
void GetAllNodeLevel(Node<T>* root, unsigned short level);

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

	// std::cout << StatDegree1NodeAmount(&nodea) << std::endl;
	// std::cout << "degree = 1: " << degree << std::endl;

	// std::cout << GetTreeHeight(&nodea) << std::endl;
	// std::cout << GetTreeWidth(&nodea) << std::endl;
	// DeleteAllLeaves(&nodea);
	// PreOrder(&nodea);
	// std::cout << std::endl;
	// InOrder(&nodea);

	// std::cout << GetNodeLevel(&nodea, &nodej) << std::endl;;
	// std::cout << GetNodeLevelV2(&nodea, &nodej) << std::endl;

	// char maxch = '\0';
	// GetMaxNodeValue(&nodea, &maxch);
	// std::cout << maxch << std::endl;

	// SwapLNodeRNode(&nodea);
	// PreOrder(&nodea);
	// std::cout << std::endl;

	// InOrder(&nodea);
	GetAllNodeLevel(&nodea, 1);

	system("pause...");
}

template <typename T>
unsigned short StatDegree1NodeAmount(Node<T>* root)
{
	unsigned short degree = 0;

	if (root)
	{
		//if (root->get_lchild() == nullptr && root->get_rchild()
		//	|| root->get_lchild() && root->get_rchild() == nullptr)
		// if (root->get_lchild() && root->get_rchild())
		if (root->get_lchild() == nullptr && root->get_rchild() == nullptr)
		{
			std::cout << root->get_data() << " ";
			++degree;
		}

		degree += StatDegree1NodeAmount(root->get_lchild()) + StatDegree1NodeAmount(root->get_rchild());
	}

	return degree;
}

template <typename T>
unsigned short GetTreeHeight(Node<T>* root)
{
	int height = 0;

	if (root)
	{
		++height;

		height += std::max(GetTreeHeight(root->get_lchild()), GetTreeHeight(root->get_rchild()));
	}

	return height;
}

template <typename T>
unsigned short GetTreeWidth(Node<T>* root)
{
	Node<T>* node;
	std::queue<Node<T>*> que;
	que.push(root);
	unsigned short maxwidth = 0;

	while (!que.empty())
	{
		unsigned short width = que.size();

		for (unsigned short wd = 0; wd < width; ++wd)
		{
			node = que.front();
			que.pop();
			if (node->get_lchild())
			{
				que.push(node->get_lchild());
			}
			if (node->get_rchild())
			{
				que.push(node->get_rchild());
			}
		}

		if (width > maxwidth)
			maxwidth = width;
	}

	return maxwidth;
}
template <typename T>
Node<T>* DeleteAllLeaves(Node<T>* root)
{
	if (root)
	{
		if (root->get_lchild() == nullptr && root->get_rchild() == nullptr)
		{
			root = nullptr;
		}
		else
		{
			root->set_lchild(DeleteAllLeaves(root->get_lchild()));
			root->set_rchild(DeleteAllLeaves(root->get_rchild()));
		}
	}

	return root;
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
unsigned short GetNodeLevel(Node<T>* root, Node<T>* idxNode)
{
	if (root)
	{
		if (root == idxNode)
			return 1;

		unsigned leftLevel = GetNodeLevel(root->get_lchild(), idxNode);

		if (leftLevel > 0)
			return leftLevel + 1;

		unsigned rightLevel = GetNodeLevel(root->get_rchild(), idxNode);

		if (rightLevel > 0)
			return rightLevel + 1;
	}

	return 0;
}

template <typename T>
unsigned short GetNodeLevelV2(Node<T>* root, Node<T>* idxNode)
{
	Node<T>* pre = nullptr;
	Node<T>* cur = root;
	std::stack<Node<T>*> stk;
	stk.push(root);

	while (!stk.empty())
	{
		if (cur)
		{
			while (cur->get_lchild())
			{
				stk.push(cur->get_lchild());
				cur = cur->get_lchild();
			}

			cur = cur->get_rchild();
		}
		else
		{
			cur = stk.top();
			if (cur->get_rchild() == nullptr || cur->get_rchild() && pre == cur->get_rchild())
			{
				// std::cout << cur->get_data() << ' ';
				if (cur == idxNode)
					return stk.size();
				stk.pop();
				pre = cur;
				cur = nullptr;
			}
			else
			{
				cur = cur->get_rchild();
				stk.push(cur);
			}
		}
	}

	return 0;
}

template <typename T>
void GetMaxNodeValue(Node<T>* root, T* max)
{
	if (root)
	{
		if (*max < root->get_data())
			*max = root->get_data();

		GetMaxNodeValue(root->get_lchild(), max);
		GetMaxNodeValue(root->get_rchild(), max);
	}
}

template <typename T>
void SwapLNodeRNode(Node<T>* root)
{
	if (root)
	{
		// std::cout << root->get_data() << ' ';
		SwapLNodeRNode(root->get_lchild());
		SwapLNodeRNode(root->get_rchild());

		// root->set_lchild(root->get_rchild());
		// root->set_rchild(root->get_lchild());
		Node<T>* lnode = root->get_lchild();
		Node<T>* rnode = root->get_rchild();
		root->set_lchild(rnode);
		root->set_rchild(lnode);
	}
}

template <typename T>
void GetAllNodeLevel(Node<T>* root, unsigned short level)
{
	if (root)
	{
		GetAllNodeLevel(root->get_lchild(), level + 1);
		GetAllNodeLevel(root->get_rchild(), level + 1);

		std::cout << root->get_data() << ' ' << "level: " << level << std::endl;
	}
}