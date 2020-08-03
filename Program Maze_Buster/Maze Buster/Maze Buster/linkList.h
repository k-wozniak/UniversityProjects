#pragma once
#include "storage.h"

// Structures
/*
* struct _ListNode: Stores the parent and the pointer to the node
*/
typedef struct _ListNode ListNode;
struct _ListNode {
	ListNode *child;
	Node *m_node;
};

/*
* struct _List: Points to the beginning of the link list and keeps the count of the entries,
*     thus, providing the basic interface to interact with the objects stored in the linkList.
*/
typedef struct _List List;
struct _List {
	ListNode *head;
	int count;
};

// Functions Declaration for List
void addFirst(List *list, Node *node);
void insertNodeSorted(List *list, Node *node);
Node *removeFirst(List *list);
void destroyLinkList(List *list);
int isEmpty(List *list);
void linkList_Test();