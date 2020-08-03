#include "linkList.h"

#include "storage.h"

#include <stdio.h>
#include <stdlib.h>

// Functions Declaration


/*
* void addFirst(List *list, Node *node): Adds a node at the link-list in the first position.
*/
void addFirst(List *list, Node *node)
{
	// Current first is saved
	ListNode *m_copy = list->head;

	// New node is created and the values are initialized
	list->head = (ListNode*)malloc(sizeof(ListNode));
	list->head->child = m_copy;
	list->head->m_node = node;

	// Counter is increased as new node added
	list->count++;
}


/*
* void insertNodeSorted(List *list, Node *node): Adds a node to the link list depending 
*     on the its heuristics. This is to speed up the A* algorithm that favorites 
*     the nodes with a lower weight.
*/
void insertNodeSorted(List *list, Node *node)
{
	// If the node has 0 or 1 entry then calls addFirst
	if ((list->count == 0) || (list->head->m_node->g > node->g))
	{
		addFirst(list, node);
		return;
	}
	
	ListNode *parentC = list->head;
	ListNode *copy = list->head->child;
	for (int i = 1; i < list->count; i++)
	{
		if (copy->m_node->g > node->g)
		{
			parentC->child = (ListNode*)malloc(sizeof(ListNode));
			parentC->child->m_node = node;
			parentC->child->child = copy;
			list->count++;
			return;
		}
		parentC = parentC->child;
		copy = copy->child;
	}
	parentC->child = (ListNode*)malloc(sizeof(ListNode));
	parentC->child->m_node = node;
	parentC->child->child = NULL;
	list->count++;
	return;
}


/*
* Node *removeFirst(List *list): Removes the first node from the link list and then 
*     returns the pointer to the removed node. 
*/
Node *removeFirst(List *list)
{
	if (list->count > 0)
	{
		Node *copy = list->head->m_node;
		ListNode *deleate = list->head;
		list->head = list->head->child;
		list->count--;
		free(deleate);
		return copy;
	}
	return NULL;
}


/*
* void destroyLinkList(List *list): Frees all the allocated memory stored in the link list to avoid any memory leakage.
*/
void destroyLinkList(List *list)
{
	while (removeFirst(list) != NULL) {};
	free(list);
}


/*
* int isEmpty(List *list): returns 1 if the list has no elements, Otherwise, returns 0
*/
int isEmpty(List *list)
{
	if (list->count <= 0)
	{
		return 1;
	}
	return 0;
}


/*
* void linkList_Test(): Make a series of automated tests to most of the functions in the linkList.h.
*     Then displays which test has been passed and which failed.
*/
void linkList_Test()
{
	// Creating List for testing
	List *t_list = (List*)malloc(sizeof(List));
	t_list->count = 0;
	t_list->head = NULL;

	// Testing: isEmpty
	if (isEmpty(t_list))
	{
		printf("Test passed: 'isEmpty(List *list)'\n");
	}
	else
	{
		printf("Test failed: 'isEmpty(List *list)'\n");
	}

	// Testing: insertNodeSorted and remove first
	Node *curNode = (Node*)malloc(sizeof(Node));
	curNode->parent = NULL;

	insertNodeSorted(t_list, curNode);
	if (curNode == removeFirst(t_list))
	{
		printf("Test passed: 'insertNodeSorted(List *list, Node *node) & *removeFirst(List *list)'\n");
	}
	else
	{
		printf("Test passed: 'insertNodeSorted(List *list, Node *node) & *removeFirst(List *list)'\n");
	}

	// Destroying created objects
	destroyLinkList(t_list);
	free(curNode);
}
