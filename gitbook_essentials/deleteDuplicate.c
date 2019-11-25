#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     struct ListNode *next;
 *     int val;
 * };
 */

typedef struct ListNode {
	struct ListNode *next;
	int val;
} ListNode;

struct ListNode* deleteDuplicates(struct ListNode* head) 
{
	if (head == NULL)
		return NULL;

	ListNode* prenode = head;
	for (ListNode* curnode = head; curnode != NULL; curnode = curnode->next) {
		if (curnode->val != prenode->val) {
			prenode->next = curnode;
			prenode = curnode;
		}
	}

	prenode->next = NULL;
	return head;
}

int main()
{
	ListNode nodea = { NULL,   2 };
	ListNode nodeb = { &nodea, 1 };
	ListNode nodec = { &nodeb, 1 };

	/* Example1: 1->1->2 */
	ListNode* newhead = deleteDuplicates(&nodec);

	for (ListNode* curnode = newhead; curnode != NULL; curnode = curnode->next) {
		printf("%d->", curnode->val);
	}
	printf("\n");

	/* Example2: 1->1->2->3->3 */
	ListNode node1 = { NULL, 3 };
	ListNode node2 = { &node1, 3 };
	ListNode node3 = { &node2, 2 };
	ListNode node4 = { &node3, 1 };
	ListNode node5 = { &node4, 1 };

	ListNode* newhead2 = deleteDuplicates(&node5);

	for (ListNode* curnode = newhead2; curnode != NULL; curnode = curnode->next) {
		printf("%d->", curnode->val);
	}
	printf("\n");

	return 0;
}