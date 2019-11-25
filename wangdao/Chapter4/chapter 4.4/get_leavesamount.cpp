#include "pch.h"

#include <iostream>

template <typename T>
struct Node
{
	typedef T ElemType;

	Node<T>* childptr;
	Node<T>* sibling;
	ElemType data;
};

int main(void)
{
	unsigned int leaves = 0;
	Node<char>* root;

	Node<char> nodec{ nullptr, nullptr, 'C' };
	Node<char> nodea{ nullptr, nullptr, 'A' };
	Node<char> nodeu{ &nodea, nullptr, 'U' };
	Node<char> nodeq{ &nodec, &nodeu, 'Q' };
	Node<char> nodel{ nullptr, nullptr, 'L' };
	Node<char> nodeg{ &nodel, nullptr, 'G' };
	Node<char> nodee{ nullptr, &nodeg, 'E' };
	Node<char> nodes{ &nodeq, &nodee, 'S' };
	Node<char> noded{ &nodes, nullptr, 'D' };

	for (Node<char>* node1 = &noded; node1; node1 = node1->childptr)
	{
		for (Node<char>* node2 = node1; node2; node2 = node2->sibling)
		{
			if (node2->childptr == nullptr)
			{
				std::cout << "leaf = " << node2->data << std::endl;
				++leaves;
			}
		}
	}

	std::cout << "leaves = " << leaves << std::endl;

	return 0;
}