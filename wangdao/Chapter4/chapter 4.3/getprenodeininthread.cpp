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
	typedef bool TagType;

public:
	Node(ElemType data, Node<ElemType>* lchild = nullptr, Node<ElemType>* rchild = nullptr, TagType ltag = false, TagType rtag = false)
		: data_(data),
		lchild_(lchild),
		rchild_(rchild),
		ltag_(ltag),
		rtag_(rtag)
	{

	}

	void set_ltag(TagType ltag) { ltag_ = ltag; }
	void set_rtag(TagType rtag) { rtag_ = rtag; }
	void set_data(ElemType data) { data_ = data; }
	void set_lchild(Node<ElemType>* lchild) { lchild_ = lchild; }
	void set_rchild(Node<ElemType>* rchild) { rchild_ = rchild; }

	TagType get_ltag() const { return ltag_; }
	TagType get_rtag() const { return rtag_; }
	ElemType get_data() const { return data_; }
	Node<ElemType>* get_lchild() const { return lchild_; }
	Node<ElemType>* get_rchild() const { return rchild_; }

private:
	TagType ltag_;
	TagType rtag_;
	ElemType data_;
	Node<ElemType>* lchild_ = nullptr;
	Node<ElemType>* rchild_ = nullptr;
};

// 先序线索化
template <typename T>
void PreThread(Node<T>* node);

template <typename T>
Node<T>* FirstNodeV1(Node<T>* node);

template <typename T>
Node<T>* NextNodeV1(Node<T>* node);

template <typename T>
void PreOrder(Node<T>* node);

// 中序线索化
/* 递归 */
template <typename T>
void InThread(Node<T>* node);

// 某个节点中序遍历的第一个节点
template <typename T>
Node<T>* FirstNode(Node<T>* p);

// 某节点中序遍历的后一个节点
template <typename T>
Node<T>* NextNode(Node<T>* p);

// 中序遍历线索二叉树
template <typename T>
void InOrder(Node<T>* node);

// 后序线索化
template <typename T>
void PostThread(Node<T>* node);

template <typename T>
Node<T>* FirstNode(Node<T>* p);

template <typename T>
Node<T>* NextNode(Node<T>* p);

template <typename T>
void PostOrder(Node<T>* node);

Node<char>* pre = nullptr;

// 求出指定结点的后序的前驱结点
template <typename T>
Node<T>* get_prenode(Node<T>* node);

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

	// 先序线索化
	// PreThread(&nodea);
	// std::cout << std::endl;
	// PreOrder(&nodea);

	// 中序线索化
	 InThread(&nodea);
	 std::cout << std::endl;
	 InOrder(&nodea);

	// 后序线索化
	//PostThread(&nodea);
	//std::cout << std::endl;
	// PostOrder(&nodea);

	system("pause...");
}

/*  
 * 让我们来思考一下这个问题
 *		1.分为是否是叶子结点 | 如果不是，不是左子树就是右子树
 *		2.是叶子节点 且他无前驱 那么后序也无前驱
 *		3.找 N 的左子树 此时注意没有左子树的情况 这是应该判断 get_lchild() 是否存在
 * */
template <typename T>
Node<T>* get_prenode(Node<T>* node)
{
	if (node->get_rtag() == false)
	{
		return node->get_rchild();
	}
	else if (node->get_ltag() == false)
	{
		return node->get_lchild();
	}
	else if (node->get_lchild() == nullptr)
	{
		return nullptr;
	}
	else
	{
		Node<T>* par = node;

		while (par->get_ltag() && par->get_lchild())
		{
			par = par->get_lchild();
		}

		if (par->get_ltag())
		{
			return par->get_lchild();
		}
		else
		{
			return nullptr;
		}
	}
}

template <typename T>
void PreThread(Node<T>* node)
{
	if (node == nullptr)
	{
		return;
	}

	std::cout << node->get_data() << ' ';

	if (node->get_lchild() == nullptr)
	{
		node->set_ltag(true);
		node->set_lchild(pre);
	}

	if (pre && pre->get_rchild() == nullptr)
	{
		pre->set_rtag(true);
		pre->set_rchild(node);
	}

	pre = node;
	if (node->get_lchild() && node->get_ltag() == false)
	{
		PreThread(node->get_lchild());
	}
	if (node->get_rchild() && node->get_rtag() == false)
	{
		PreThread(node->get_rchild());
	}
}

template <typename T>
Node<T>* FirstNodeV1(Node<T>* node)
{
	return node;
}

template <typename T>
Node<T>* NextNodeV1(Node<T>* node)
{
	if (node->get_ltag())
		return FirstNodeV1(node->get_rchild());
	else
		return node->get_lchild();
}

template <typename T>
void PreOrder(Node<T>* node)
{
	//for (Node<T>* root = FirstNode(node); root; root = NextNode(root))
	//{
	//	std::cout << root->get_data() << ' ';
	//}

	//std::cout << std::endl;

	for (auto root = FirstNodeV1(node); root; root = NextNodeV1(root))
	{
		std::cout << root->get_data() << ' ';
	}

	std::cout << std::endl;
}

template <typename T>
void InThread(Node<T>* node)
{
	if (node)
	{
		InThread(node->get_lchild());
		if (node->get_lchild() == nullptr)
		{
			node->set_ltag(true);
			node->set_lchild(pre);
		}
		if (pre != nullptr && pre->get_rchild() == nullptr)
		{
			pre->set_rtag(true);
			pre->set_rchild(node);
		}

		std::cout << node->get_data() << ' ';

		pre = node;
		InThread(node->get_rchild());
	}
}

template <typename T>
Node<T>* FirstNode(Node<T>* p)
{
	// Node<T>* next = p->get_rchild();
	Node<T>* next = p;

	while (next && next->get_ltag() == false)
	{
		next = next->get_lchild();
	}

	return next;
}

template <typename T>
Node<T>* NextNode(Node<T>* p)
{
	if (p->get_rtag())
		return p->get_rchild();
	else
		return FirstNode(p->get_rchild());
}

template <typename T>
void InOrder(Node<T>* node)
{
	for (Node<T>* root = FirstNode(node); root; root = NextNode(root))
	{
		std::cout << root->get_data() << ' ';
	}

	std::cout << std::endl;
}

template <typename T>
void PostThread(Node<T>* node)
{
	if (node == nullptr)
		return;

	PostThread(node->get_lchild());
	PostThread(node->get_rchild());

	std::cout << node->get_data() << ' ';
	if (node->get_lchild() == nullptr)
	{
		node->set_ltag(true);
		node->set_lchild(pre);
	}

	if (pre && pre->get_rchild() == nullptr)
	{
		pre->set_rtag(true);
		pre->set_rchild(node);
	}

	pre = node;
}
