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

/* 依据先序遍历和中序遍历去构建一棵二叉树 */
/* 递归v1 */
template <typename T>
Node<T>* ConstructorATreeFromPreOrderAndInOrderV1(char preorder[], char inorder[], size_t length); /* 一样的，不过是修改地址罢了 */

/* 递归v2 */
template <typename T>
Node<T>* ConstructorATreeFromPreOrderAndInOrderV2(char preorder[], size_t pleft, size_t pright, char inorder[], size_t ileft, size_t iright);

/* 测试用例 */
template <typename T>
void Traverse(Node<T>* root);

template <typename T>
void PreOrder(Node<T>* root);

template <typename T>
void InOrder(Node<T>* root);

template <typename T>
void PostOrder(Node<T>* root);

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

	// Node<char>* root = ConstructorATreeFromPreOrderAndInOrderV1<char>(preOrder, inOrder, );
	// Node<char>* root = ConstructorATreeFromPreOrderAndInOrderV2<char>(preOrder, 0, strlen(preOrder), inOrder, 0, strlen(inOrder));

	PrintPostOrder<char>(preOrder, inOrder);

	// Traverse(root);

	system("pause...");
}

template <typename T>
Node<T>* ConstructorATreeFromPreOrderAndInOrderV2(char* preorder, size_t pleft, size_t pright, char *inorder, size_t ileft, size_t iright)
{
	if (pleft >= pright || ileft >= iright)
		return nullptr;

	Node<T>* root = new Node<T>(preorder[pleft]);
	// root->set_data(preorder[pleft]);

	size_t midst1 = 0;

	/* 现在找出左子树 + 找出右子树 */
	for (size_t i = ileft; i < iright; ++i)
	{
		if (preorder[pleft] == inorder[i])
		{
			midst1 = i;
			break;
		}
	}

	root->set_lchild(ConstructorATreeFromPreOrderAndInOrderV2<T>(preorder, pleft + 1, pleft + 1 + midst1 - ileft, inorder, ileft, midst1));
	root->set_rchild(ConstructorATreeFromPreOrderAndInOrderV2<T>(preorder, pleft + 1 + midst1 - ileft, pright, inorder, midst1 + 1, iright));

	return root;
}

template <typename T>
void Traverse(Node<T>* root)
{
	PreOrder(root);
	std::cout << std::endl;

	InOrder(root);
	std::cout << std::endl;

	PostOrder(root);
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
void PostOrder(Node<T>* root)
{
	if (root)
	{
		PostOrder(root->get_lchild());
		PostOrder(root->get_rchild());
		std::cout << root->get_data() << ' ';
	}
}