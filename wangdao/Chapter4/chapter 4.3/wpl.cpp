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
	typedef int Weight;

public:
	Node(ElemType data, Node<ElemType>* lchild = nullptr, Node<ElemType>* rchild = nullptr, Weight weight = 1)
		: data_(data), 
		  lchild_(lchild), 
		  rchild_(rchild),
		  weight_(weight)
	{

	}

	void set_weight(Weight weight) { weight_ = weight; }
	void set_data(ElemType data) { data_ = data; }
	void set_lchild(Node<ElemType>* lchild) { lchild_ = lchild; }
	void set_rchild(Node<ElemType>* rchild) { rchild_ = rchild; }

	Weight get_weight() const { return weight_; }
	ElemType get_data() const { return data_; }
	Node<ElemType>* get_lchild() const { return lchild_; }
	Node<ElemType>* get_rchild() const { return rchild_; }

private:
	Weight weight_;
	ElemType data_;
	Node<ElemType>* lchild_ = nullptr;
	Node<ElemType>* rchild_ = nullptr;
};

// 计算路径的权重
template <typename T>
int get_pathweight(Node<T>* root, Node<T>* node);

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

	std::cout << "weight = " << get_pathweight(&nodea, &noded) << std::endl;

	system("pause...");
}

template <typename T>
int get_pathweight(Node<T>* root, Node<T>* node)
{
	int sumweight = 0;
	Node<T>* pre = nullptr;
	std::stack<Node<T>*> stk;

	stk.push(root);

	while (!stk.empty())
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
				//if (root == node)
				//	break;

				if (root->get_lchild() == nullptr && root->get_rchild() == nullptr)
				{
					sumweight += root->get_weight() * stk.size();
				}

				stk.pop();
				pre = root;
				root = nullptr;
			}
		}
	}

	return sumweight;
}