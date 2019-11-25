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

// 先序遍历
/* 递归 */
template <typename T>
void PreOrderV1(Node<T>* node);
/* 辅助栈 */
template <typename T>
void PreOrderV2(Node<T>* node);
template <typename T>
void PreOrderV3(Node<T>* node);
/* 线索化遍历(Miror) */
template <typename T>
void PreOrderV4(Node<T>* node);

// 中序遍历
/* 递归 */
template <typename T>
void InOrderV1(Node<T>* node);
/* 辅助栈 */
template <typename T>
void InOrderV2(Node<T>* node);
template <typename T>
void InOrderV3(Node<T>* node);
/* 线索化遍历(Miror) */
template <typename T>
void InOrderV4(Node<T>* node);

// 后序遍历
/* 递归 */
template <typename T>
void PostOrderV1(Node<T>* node);
/* 辅助栈 */
template <typename T>
void PostOrderV2(Node<T>* node);
template <typename T>
void PostOrderV3(Node<T>* node);
template <typename T>
void PostOrderV4(Node<T>* node);
template <typename T>
void PostOrderV6(Node<T>* node);
/* 线索化遍历(Miror) */
template <typename T>
void PostOrderV5(Node<T>* node);

// 层次遍历
template <typename T>
/* 队列 */
void LevelOrderV1(Node<T>* node);

template <typename T>
void reverse(Node<T>* head, Node<T>* tail);

template <typename T>
void reverseprint(Node<T>* head, Node<T>* tail);

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

	// 递归测试
	// PreOrderV1(&nodea);
	// std::cout << std::endl;
	// InOrderV1(&nodea);
	// std::cout << std::endl;
	PostOrderV1(&nodea);
	std::cout << std::endl;

	// 辅助栈遍历
	// PreOrderV2(&nodea);
	// PreOrderV3(&nodea);
	// InOrderV2(&nodea);
	// InOrderV3(&nodea);
	// PostOrderV2(&nodea);
	// PostOrderV3(&nodea);
	// std::cout << std::endl;

	// 线索化遍历
	// PreOrderV4(&nodea);
	// std::cout << std::endl;
	// InOrderV4(&nodea);
	// std::cout << std::endl;
	// PostOrderV5(&nodea);
	// std::cout << std::endl;

	// 层次遍历
	LevelOrderV1(&nodea);
	std::cout << std::endl;

	system("pause...");
}

template <typename T>
void PreOrderV1(Node<T>* node)
{
	if (node)
	{
		std::cout << node->get_data() << ' ';
		PreOrderV1(node->get_lchild());
		PreOrderV1(node->get_rchild());
	}
}

template <typename T>
void InOrderV1(Node<T>* node)
{
	if (node)
	{
		InOrderV1(node->get_lchild());
		std::cout << node->get_data() << ' ';
		InOrderV1(node->get_rchild());
	}
}

template <typename T>
void PostOrderV1(Node<T>* node)
{
	if (node)
	{
		PostOrderV1(node->get_lchild());
		PostOrderV1(node->get_rchild());
		std::cout << node->get_data() << ' ';
	}
}

template <typename T>
void PreOrderV2(Node<T>* node)
{
	std::stack<Node<T>*> stk;
	
	while (!stk.empty() || node)
	{
		if (node)
		{
			stk.push(node);
			std::cout << node->get_data() << ' ';
			node = node->get_lchild();
		}
		else
		{
			node = stk.top();
			stk.pop();
			node = node->get_rchild();
		}
	}
}

template <typename T>
void PreOrderV3(Node<T>* node)
{
	std::stack<Node<T>*> stk;
	stk.push(node);
	while (!stk.empty())
	{
		node = stk.top();
		stk.pop();
		std::cout << node->get_data() << ' ';
		if (node->get_rchild()) {
			stk.push(node->get_rchild());
		}
		if (node->get_lchild()) {
			stk.push(node->get_lchild());
		}
	}
}

template <typename T>
void InOrderV2(Node<T>* node)
{
	std::stack<Node<T>*> stk;
	while (!stk.empty() || node)
	{
		//if (node)
		//{
		//	while (node->get_lchild())
		//	{
		//		stk.push(node);
		//		node = node->get_lchild();
		//	}

		//	std::cout << node->get_data() << ' ';
		//	node = node->get_rchild();
		//}
		//else
		//{
		//	node = stk.top();
		//	stk.pop();
		//	std::cout << node->get_data() << ' ';
		//	node = node->get_rchild();
		//}
		if (node)
		{
			stk.push(node);
			node = node->get_lchild();
		}
		else
		{
			node = stk.top();
			stk.pop();
			std::cout << node->get_data() << ' ';
			node = node->get_rchild();
		}
	}
}

template <typename T>
void InOrderV3(Node<T>* node)
{
	std::stack<Node<T>*> stk;

	while (!stk.empty() || node)
	{
		if (node)
		{
			stk.push(node);
			node = node->get_lchild();
		}
		else
		{
			node = stk.top();
			stk.pop();
			std::cout << node->get_data() << ' ';
			node = node->get_rchild();
		}
	}
}

template <typename T>
void PostOrderV2(Node<T>* node)
{
	std::vector<T> res;
	std::stack<Node<T>*> stk;
	stk.push(node);

	while (!stk.empty())
	{
		node = stk.top();
		stk.pop();
		res.insert(res.begin(), node->get_data());
		if (node->get_lchild())
			stk.push(node->get_lchild());
		if (node->get_rchild())
			stk.push(node->get_rchild());
	}

	for (typename std::vector<T>::size_type idx = 0; idx < res.size(); ++idx)
	{

	}

	std::copy(std::cbegin(res), std::cend(res), std::ostream_iterator<T>(std::cout, " "));
}

template <typename T>
void PostOrderV3(Node<T>* node)
{
	std::vector<T> res;
	std::stack<Node<T>*> stk;

	while (!stk.empty() || node)
	{
		if (node)
		{
			stk.push(node);
			res.insert(std::begin(res), node->get_data());
			node = node->get_rchild();
		}
		else
		{
			node = stk.top();
			stk.pop();
			node = node->get_lchild();
		}
	}

	std::copy(std::cbegin(res), std::cend(res), std::ostream_iterator<T>(std::cout, " "));
}

template <typename T>
void PostOrderV4(Node<T>* node)
{
	std::stack<Node<T>*> stk1;
	std::stack<Node<T>*> stk2; /* use to revser the output  */

	//while (!stk1.empty() || node)
	//{
	//	if (node)
	//	{
	//		stk1.push(node);
	//		stk2.push(node);
	//		node = node->get_rchild();
	//	}
	//	else
	//	{
	//		node = stk1.top();
	//		stk1.pop();
	//		node = node->get_lchild();
	//	}
	//}

	stk1.push(node);
	while (!stk1.empty())
	{
		node = stk1.top();
		stk1.pop();
		stk2.push(node);
		if (node->get_lchild()) 
		{
			stk1.push(node->get_lchild());
		}
		if (node->get_rchild())
		{
			stk1.push(node->get_rchild());
		}
	}

	std::copy(std::cbegin(stk2), std::cend(stk2), std::ostream_iterator<T>(std::cout, " "));
}

template <typename T>
void PreOrderV4(Node<T>* node)
{
	Node<T>* pre = node;
	Node<T>* cur = node;

	while (pre)
	{
		if (pre->get_lchild())
		{
			cur = pre->get_lchild();
			while (cur->get_rchild() && cur->get_rchild() != pre)
			{
				cur = cur->get_rchild();
			}

			if (cur->get_rchild() == pre)
			{
				cur->set_rchild(nullptr);
				pre = pre->get_rchild();
			}
			else
			{
				std::cout << pre->get_data() << ' ';
				cur->set_rchild(pre);
				pre = pre->get_lchild();
			}
		}
		else
		{
			std::cout << pre->get_data() << ' ';
			pre = pre->get_rchild();
		}
	}
}

template <typename T>
void InOrderV4(Node<T>* node)
{
	Node<T>* pre = node;
	Node<T>* cur = node->get_lchild();

	while (pre)
	{
		if (pre->get_lchild())
		{
			cur = pre->get_lchild();
			while (cur->get_rchild() && pre != cur->get_rchild())
			{
				cur = cur->get_rchild();
			}

			if (cur->get_rchild() == pre)
			{
				// destroy threat
				std::cout << pre->get_data() << ' ';
				cur->set_rchild(nullptr);
				pre = pre->get_rchild();
			}
			else
			{
				// construct threat
				cur->set_rchild(pre);
				pre = pre->get_lchild();
			}
		}
		else
		{
			std::cout << pre->get_data() << ' ';
			pre = pre->get_rchild();
		}
	}
}

template <typename T>
void PostOrderV6(Node<T>* node)
{
	// 这个使用一个标志来处理是否曾经遍历过
	NodeT<T>* pre = nullptr;
	std::stack<Node<T>*> stk;

	while (!stk.empty() || node)
	{
		if (node)
		{
			stk.push(node);
			node = node->get_lchild();
		}
		else
		{
			node = stk.top();

			if (node->get_rchild() && node->get_rchild() != pre)
			{
				// 我的右节点没有遍历
				node = node->get_rchild();
			}
			else
			{
				std::cout << node->get_data() << ' ';
				stk.pop();
				pre = node;
				node = nullptr;
			}
			
		}
	}
	
}

template <typename T>
void PostOrderV5(Node<T>* node)
{
	Node<T> tempNode{'X'};
	tempNode.set_lchild(node);

	Node<T>* pre = &tempNode;
	Node<T>* cur = &tempNode;

	while (pre)
	{
		if (pre->get_lchild())
		{
			cur = pre->get_lchild();
			while (cur->get_rchild() && cur->get_rchild() != pre)
			{
				cur = cur->get_rchild();
			}

			if (cur->get_rchild() == pre)
			{
				reverseprint(pre->get_lchild(), cur);
				pre = pre->get_rchild();
				cur->set_rchild(nullptr);
			}
			else
			{
				cur->set_rchild(pre);
				pre = pre->get_lchild();
			}
		}
		else
		{
			pre = pre->get_rchild();
		}
	}
}

template <typename T>
void reverseprint(Node<T>* head, Node<T>* tail)
{
	reverse(head, tail);

	//for (Node<T>* cur = tail; cur != head; cur = cur->get_rchild())
	//{
	//	std::cout << cur->get_data() << ' ';
	//}
	Node<T>* cur = tail;
	while (true)
	{
		std::cout << cur->get_data() << ' ';
		
		if (cur == head)
		{
			break;
		}

		cur = cur->get_rchild();
	}


	reverse(tail, head);
}

template <typename T>
void reverse(Node<T>* head, Node<T>* tail)
{
	Node<T>* pre = head;
	Node<T>* cur = pre->get_rchild();
	Node<T>* next = cur->get_rchild();

	if (head == tail)
		return;

	while (true)
	{
		next = cur->get_rchild();
		cur->set_rchild(pre);
		pre = cur;
		cur = next;

		if (pre == tail)
			break;
	}
}

template <typename T>
void LevelOrderV1(Node<T>* node)
{
	std::queue<Node<T>*> que;

	que.push(node);

	while (!que.empty())
	{
		node = que.front();
		que.pop();

		std::cout << node->get_data() << ' ';

		if (node->get_lchild())
			que.push(node->get_lchild());

		if (node->get_rchild())
			que.push(node->get_rchild());
	}
}

/*
参考链接:
	https://zhidao.baidu.com/question/292665883.html 	(盗图....)
	https://www.cnblogs.com/grandyang/p/4146981.html	(先序遍历)
	https://www.cnblogs.com/grandyang/p/4297300.html	(中序遍历)
	https://www.cnblogs.com/grandyang/p/4251757.html	(后序遍历)
	https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html	(MorrisTraversal)
*/