// Reference to <<Data structure and algorithm analysis in C>> Second Edition
#include "pch.h"

#include <stack>
#include <iostream>
#include <algorithm>
#include <functional>

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
typedef char ElementType;

struct AvlNode
{
	ElementType Element;
	AvlTree		Left;
	AvlTree		Right;
	int			Height;
};

static int Height(Position P)
{
	if (P == nullptr)
		return -1;
	else
		return P->Height;
}

// This function can be called only if K2 has a left child
// Perform a rotate between a node (K2) and its left child
// Update heights, then return new root
static Position
SingleRotateWithLeft(Position K2);

static Position
SingleRotateWithRight(Position K2);

// This function can be called only if K3 has a left
// child and k3's left child has a right child
// do the left-right double rotation
// update heights, then return new root
static Position
DoubleRotateWithLeft(Position K3);

static Position
DoubleRotateWithRight(Position K3);

AvlTree Insert(ElementType X, AvlTree T)
{
	if (T == nullptr)
	{
		// Create and return a one-node tree
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if (T == nullptr)
		{
			std::cout << "Out of space!!!" << std::endl;
		}
		else
		{
			T->Element = X;
			T->Height = 0;
			T->Left = nullptr;
			T->Right = nullptr;
		}
	}
	else if (X < T->Element){
		T->Left = Insert(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->Element) {
		T->Right = Insert(X, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}
	/* Else X is in the tree already; we'll do nothing */

	T->Height = std::max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

int main()
{
	AvlTree avltree = nullptr;
	
	ElementType datas[] = { '3','2','1','4','5','6','7' };
	for (unsigned short i = 0; i < sizeof(datas) / sizeof(ElementType); ++i)
	{
		avltree = Insert(datas[i], avltree);
	}
}

static Position
SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = std::max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = std::max(Height(K1->Left), Height(K1->Right)) + 1;

	return K1;
}

static Position
SingleRotateWithRight(Position K1)
{
	Position K2;

	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = std::max(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = std::max(Height(K2->Left), Height(K2->Right)) + 1;

	return K2;
}

static Position
DoubleRotateWithLeft(Position K3)
{
	// Rotate between K1 and K2
	K3->Left = SingleRotateWithRight(K3->Left);

	// Rotate between K3 and K2
	return SingleRotateWithLeft(K3);
}

static Position
DoubleRotateWithRight(Position K3)
{
	// Rotate between K1 and K2
	K3->Right = SingleRotateWithLeft(K3->Right);

	// Rotate between K3 and K2
	return SingleRotateWithRight(K3);
}
