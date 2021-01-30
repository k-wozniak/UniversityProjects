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

/* Function: addFirst
 * ------------------
 * Appends a node at the beginning of the link-list
 *
 * list: The list to which the node will be added
 * node: Item to be added
 */
void addFirst(List *list, Node *node);

/* Function: insertNodeSorted
 * --------------------------
 * Inserts the node based on the heuristics. Used for the A* algorithm.
 *
 * list: The list to which the node will be added
 * node: Item to be added
 */
void insertNodeSorted(List *list, Node *node);

/* Function: removeFirst
 * ---------------------
 * Removes and returns the first item from the list.
 *
 * list: the list from which the item needs to be removed
 *
 * returns: the node removed
 */
Node *removeFirst(List *list);

/* Function: destroyLinkList
 * -------------------------
 * Deallocate memory and removed the list
 *
 * list: list to destroy
 */
void destroyLinkList(List *list);

/* Function: isEmpty
 * -----------------
 * Checks if the list has any nodes
 *
 * list: List to be checked
 *
 * returns: 0 for false and 1 for true
 */
int isEmpty(List *list);

/* Function: linkList_Test
 * -----------------------
 * Runs a set of unit tests
 */
void linkList_Test();