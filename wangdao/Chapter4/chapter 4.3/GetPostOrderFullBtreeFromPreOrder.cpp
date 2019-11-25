// 王道真垃圾 我还要去考浙大的研究生 真的讽刺
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

// 满二叉树 依据先序求后序
void GetPostOrderFullBtreeFromPreOrder(char preorder[], int preleft, int preright,
	char postorder[], int postleft, int postright);

void GenFullBtree(char preorder[], size_t len);

// 后序遍历递归版
void PostOrder(char[], size_t idx, size_t length);

// 链接所有叶节点
template <typename T>
void LinkAllNode(Node<T>* node);

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

	// char preorder[] = "ABDHLEJKCFLMGNO";
	char preorder[] = "ABDECFG";
	char * postorder = new char[strlen(preorder)];

	for (int i = 0; i < strlen(preorder); ++i)
	{
		postorder[i] = '\0';
	}

	GetPostOrderFullBtreeFromPreOrder(preorder, 0, strlen(preorder), postorder, 0, strlen(preorder));

	for (int i = 0; i < strlen(preorder); ++i)
	{
		std::cout << postorder[i] << ' ';
	}

	// LinkAllNode(&nodea);

	system("pause...");
}

void GetPostOrderFullBtreeFromPreOrder(char preorder[], int preleft, int preright,
	char postorder[], int postleft, int postright)
{
	if (preleft >= preright)
		return;

	postorder[postright - 1] = preorder[preleft];
	int half = (preright - preleft - 1) / 2;
	GetPostOrderFullBtreeFromPreOrder(preorder, preleft + 1, preleft + half + 1, postorder, postleft, postleft + half);
	GetPostOrderFullBtreeFromPreOrder(preorder, preleft + half + 1, preright, postorder, postleft + half, postright - 1);
}

template <typename T>
void LinkAllNode(Node<T>* node)
{
	Node<T>* head = nullptr;
	Node<T>* preleaf = nullptr;
	Node<T>* pre = nullptr;
	std::stack<Node<T>*> stk;
	stk.push(node);
	
	while (!stk.empty() || node)
	{
		if (node)
		{
			while (node->get_lchild())
			{
				stk.push(node->get_lchild());
				node = node->get_lchild();
			}

			node = node->get_rchild();
		}
		else
		{
			node = stk.top();
			if (node->get_rchild() && node->get_rchild() != pre)
			{
				stk.push(node->get_rchild());
				node = node->get_rchild();
			}
			else
			{
				if (node->get_rchild() == nullptr && node->get_lchild() == nullptr)
				{
					if (preleaf == nullptr)
					{
						preleaf = node;
						head = preleaf;
					}
					else
					{
						preleaf->set_rchild(node);
						preleaf = node;
					}
				}

				stk.pop();
				// std::cout << node->get_data() << ' ';
				pre = node;
				node = nullptr;
			}
		}
	}

	do
	{
		std::cout << head->get_data() << ' ';
		head = head->get_rchild();
	} while (head != nullptr);

	std::cout << std::endl;
}