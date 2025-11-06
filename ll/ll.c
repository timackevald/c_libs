/**
 * @file ll.c
 * @brief Doubly linked list implementation
 * @author Tim Ackevald
 * @date 2025-10
 */

#include "ll.h"
#include <stdlib.h>
#include <string.h>



/**
 * @brief Initialize a new list
 * @param self Pointer to list pointer to initialize
 * @return RET_OK on success, RET_FAIL on allocation failure
 */
int8_t ll_list_init(struct ll_list *self)
{
	if (!self) return RET_FAIL;
	memset(self, 0, sizeof(*self));

	return RET_OK;
}

/**
 * @brief Deinitialize a list object.
 * @param self Pointer to list object
 * @return RET_OK on success, RET_FAIL if self is NULL
 * Frees all nodes in the list but NOT the list itself.
 * List memory is owned by caller (might be embedded/stack).
 */

int8_t ll_list_deinit(struct ll_list *self)
{
	if (!self) return RET_FAIL;
	struct ll_node *curr_node = self->head;
	while (curr_node)
	{
		struct ll_node *next  = curr_node->next;
		free(curr_node);
		curr_node = next;
	}

	self->head = NULL;
	self->tail = NULL;
	self->size = 0;
	
	return RET_OK;
}

/**
 * @brief Create a new node associated with a list
 * @param self Pointer to node pointer to initialize
 * @param list Pointer to list this node belongs to
 * @return 0 on success, -1 on failure
 */
int8_t ll_node_init(struct ll_node *self, struct ll_list *list)
{
	if (!self || !list) return RET_FAIL;
	memset(self, 0, sizeof(*self));
	
	self->list = list;
	self->next = NULL;
	self->prev = NULL;

	return RET_OK;
}

/**
 * @brief Append node to tail of list.
 * @param self Pointer to list object
 * @param node Pointer to node to append
 * @return RET_OK on success, RET_FAIL if parameters invalid.
 */
int8_t ll_list_append(struct ll_list *self, struct ll_node *node)
{
	if (!self || !node) return RET_FAIL;
	if (node->list != self) return RET_FAIL;

	if (!self->tail)
	{
		self->head = node;
		self->tail = node;
		node->next = NULL;
		node->prev = NULL;
	}
	else
	{
		node->prev = self->tail;
		node->next = NULL;
		self->tail->next = node;
	    self->tail = node;
	}

	self->size++;
	
	return RET_OK;
}

/**
 * @brief Prepend node to head of its associated list
 * @param self Pointer to node pointer
 * @return RET_OK on success, RET_FAIL if node or list is invalid
 * 
 * If list is empty, node becomes both head and tail.
 * Otherwise, node is linked before current head.
 */
int8_t ll_list_prepend(struct ll_list *self, struct ll_node *node)
{
	if (!self || !node) return RET_FAIL;
	if (node->list != self) return RET_FAIL;

	if (!self->head)
	{
		self->head = node;
		self->tail = node;
		node->next = NULL;
		node->prev = NULL;		
	}
	else
	{
		node->next = self->head;
		node->prev = NULL;
		self->head->prev = node;
		self->head = node;
	}

	self->size++;
	
	return RET_OK;
}

/**
 * @brief Remove a node from list.
 * @param self Pointer to list object
 * @param node Pointer to node to remove
 * @return RET_OK on success, RET_FAIL if parameters invalid
 */
int8_t ll_list_remove(struct ll_list *self, struct ll_node *node)
{
	if (!self || !node) return RET_FAIL;
	if (node->list != self) return RET_FAIL;

	if (!node->prev)
	{
		self->head = node->next;
	}
	else
	{
		node->prev->next = node->next;
	}

	if (!node->next)
	{
		self->tail = node->prev;
	}
	else
	{
		node->next->prev = node->prev;
	}

	node->next = NULL;
	node->prev = NULL;

	self->size--;
	
	return RET_OK;
}
