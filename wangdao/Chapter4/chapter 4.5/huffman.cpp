#include "pch.h"

#include <stack>
#include <iostream>
#include <functional>

#define N 4
#define MAXVALUE  10000

template <typename T>
class Node
{
	typedef T ElemType;
	typedef int Weight;

public:
	Node(Weight weight = 0, ElemType data = ' ', Node<T>* lchild = nullptr, Node<T>* rchild = nullptr)
		: weight_(weight), data_(data), lchild_(lchild), rchild_(rchild)
	{

	}

	void set_data(ElemType data) { data_ = data; }
	void set_weight(Weight weight) { weight_ = weight; }
	void set_lchild(Node<T>* lchild) { lchild_ = lchild; }
	void set_rchild(Node<T>* rchild) { rchild_ = rchild; }

	Weight get_weight() const { return weight_; }
	ElemType get_data() const { return data_; }
	Node<T>* get_lchild() const { return lchild_; }
	Node<T>* get_rchild() const { return rchild_; }

private:
	Weight weight_;
	ElemType data_;
	Node<T>* lchild_;
	Node<T>* rchild_;
};

// PreOrder
template <typename T>
void PreOrder(Node<T>* node);

// InOrder
template <typename T>
void InOrder(Node<T>* node);

// Haffman node sort by power
template <typename T>
void SortHaffmanNode(Node<T>* nodes, unsigned short length);

// Haffman
template <typename T>
void ConstructHuffmanTree(Node<T>* nodes[], T datas[], int weights[], unsigned short length);

// Haffman decode
template <typename T>
void HaffmanDecode(Node<T>* root, char code[], unsigned short len);

int main()
{
	Node<char>* nodes[2 * N];

	for (unsigned short i = 0; i < 2 * N; ++i)
	{
		nodes[i] = new Node<char>;
	}

	int weights[N] = { 7, 5, 2, 4 };
	char datas[N] = {'a', 'b', 'c', 'd'};

	ConstructHuffmanTree<char>(nodes, datas, weights, N);
	// PreOrder(nodes[2 * N - 2]);
	// InOrder(nodes[2 * N - 1]);

	char codes[] = "110100111";
	HaffmanDecode<char>(nodes[2 * N - 2], codes, sizeof(codes) / sizeof(char));
}

// 想的有问题
//template <typename T>
//void SortHaffmanNode(Node<T>* nodes[], unsigned short length)
//{
//	bool flag = true;
//
//	for (unsigned short i = 0; i < length && flag; ++i)
//	{
//		for (unsigned short j = 0; j < n - i; ++j)
//		{
//			flag = false;
//			if (nodes[j] > arr[j + 1])
//			{
//				flag = true;
//
//				Node<T>* tempNode = nodes[j];
//				nodes[j] = nodes[j + 1];
//				nodes[j + 1] = tempNode;
//			}
//		}
//	}
//}

template <typename T>
void ConstructHuffmanTree(Node<T>* nodes[], T datas[], int weights[], unsigned short length)
{
	if (length <= 1)
		return;

	unsigned short minindex1{ 0 }, minindex2{ 0 };
	unsigned short minweight1{ MAXVALUE }, minweight2{ MAXVALUE };

	// Initialization
	for (unsigned short len = 0; len < length; ++len)
	{
		nodes[len]->set_data(datas[len]);
		nodes[len]->set_lchild(nullptr);
		nodes[len]->set_rchild(nullptr);
		nodes[len]->set_weight(weights[len]);
	}

	// SortHaffmanNode(nodes, length);

	// loop construct
	for (unsigned short i = 0; i < length - 1; ++i)
	{
		minindex1 = 0;
		minindex2 = 0;
		minweight1 = MAXVALUE;
		minweight2 = MAXVALUE;

		for (unsigned short j = 0; j < length + i; ++j)
		{
			if (nodes[j] == nullptr)
			{
				continue;
			}
			else if (nodes[j]->get_weight() < minweight1)
			{
				minindex2 = minindex1;
				minweight2 = minweight1;
				minindex1 = j;
				minweight1 = nodes[j]->get_weight();
			}
			else if (nodes[j]->get_weight() < minweight2)
			{
				minindex2 = j;
				minweight2 = nodes[j]->get_weight();
			}
		}

		nodes[length + i]->set_lchild(nodes[minindex1]);
		nodes[length + i]->set_rchild(nodes[minindex2]);
		nodes[length + i]->set_weight(minweight1 + minweight2);
		nodes[minindex1] = nullptr;
		nodes[minindex2] = nullptr;

		std::cout << "minindex.weight and minindex.weight in round " << i << ": "<< minweight1 << ", " << minweight2 << std::endl;
	}
}

template <typename T>
void PreOrder(Node<T>* node)
{
	if (node)
	{
		InOrder(node->get_lchild());
		std::cout << "(" << node->get_data() << ", " << node->get_weight() << ")" << std::endl;
		InOrder(node->get_rchild());
	}
}

template <typename T>
void InOrder(Node<T>* node)
{
	if (node)
	{
		InOrder(node->get_lchild());
		std::cout << "(" << node->get_data() << ", " << node->get_weight() << ")" << std::endl;
		InOrder(node->get_rchild());
	}
}

template <typename T>
void HaffmanDecode(Node<T>* root, char code[], unsigned short len) 
{
	Node<T>* node = root;
	for (unsigned short idx = 0; idx < len; ++idx)
	{
		if (node->get_lchild() == nullptr && node->get_rchild() == nullptr)
		{
			std::cout << node->get_data() << " ";
			node = root;
		}
		if (code[idx] == '0')
		{
			node = node->get_lchild();
		}
		else
		{
			node = node->get_rchild();
		}
	}
}