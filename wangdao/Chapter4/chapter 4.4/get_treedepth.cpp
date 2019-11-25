#include "pch.h"

#include <stack>
#include <queue>
#include <iostream>

template <typename T>
struct Node
{
	typedef T ElemType;

	Node<T>* childptr;
	Node<T>* sibling;
	ElemType data;
};

// 题目要求: 设计求树的深度
template <typename T>
unsigned short get_treedepth(Node<T>* node);

template <typename T>
unsigned short get_treedepthV2(Node<T>* node);

template <typename T>
unsigned short get_treedepthV3(Node<T>* node);

template <typename T>
unsigned short get_treedepthV4(Node<T>* node);

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

	std::cout << "depth = " << get_treedepth(&noded) << std::endl;
	std::cout << "By version2: get depth = " << get_treedepthV2(&noded) << std::endl;
	std::cout << "By version3: get depth = " << get_treedepthV3(&noded) << std::endl;
	std::cout << "By version4: get depth = " << get_treedepthV4(&noded) << std::endl;

	return 0;
}

/*
 * 思考一下: 能否将中间的循环消除实现更彻底的递归?
 */
template <typename T>
unsigned short get_treedepth(Node<T>* node)
{
	if (node == nullptr)
		return 0;

	unsigned short depth1 = get_treedepth(node->childptr) + 1;
	unsigned short maxsiblingdepth = 0;

	for (Node<T>* sibling = node->sibling; sibling; sibling = sibling->sibling)
	{
		unsigned short depth = get_treedepth(sibling->childptr) + 1;
		if (depth > maxsiblingdepth)
		{
			maxsiblingdepth = depth;
		}
	}

	return maxsiblingdepth > depth1 ? maxsiblingdepth: depth1;
}

/*
 * 还是不喜欢递归 
 */

template <typename T>
unsigned short get_treedepthV2(Node<T>* node)
{
	if (node == nullptr)
		return 0;

	unsigned short depth1 = get_treedepth(node->childptr) + 1;
	unsigned short depth2 = get_treedepth(node->sibling);

	return depth1 > depth2 ? depth1 : depth2;
}

/*
 * 写的时候突然觉得 队列真的不错haha 
 */
template <typename T>
unsigned short get_treedepthV3(Node<T>* node)
{
	if (node == nullptr)
		return 0;

	unsigned short depth = 0;
	std::stack<Node<T>*> stk;
	stk.push(node);

	while (!stk.empty() || node)
	{
		if (node)
		{
			while (node->childptr)
			{
				stk.push(node->childptr);
				node = node->childptr;
			}

			// 这条路到底了
			if (stk.size() > depth)
				depth = stk.size();
			node = node->childptr;
		}
		else
		{
			node = stk.top();
			stk.pop();
			node = node->sibling;
			if (node)
				stk.push(node);
		}
	}

	return depth;
}

template <typename T>
unsigned short get_treedepthV4(Node<T>* node)
{
	if (node == nullptr)
		return 0;
	
	unsigned short depth = 0;
	std::queue<Node<T>*> que;
	que.push(node);

	while (!que.empty())
	{
		unsigned short size = que.size();
		while (size--)
		{
			node = que.front();
			que.pop();
			for (Node<T>* child = node->childptr; child; child = child->sibling)
			{
				que.push(child);
			}
		}

		++depth;
	}

	return depth;
}