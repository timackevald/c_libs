/**
 * @file ll.c
 * @brief Doubly linked list implementation
 * @author Tim Ackevald
 * @date 2025-10
 */

#include "ll.h"
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Return code enumeration
 */
typedef enum ret_code
{
	RET_FAIL = -1,
	RET_OK
} ret_code_t;

/**
 * @brief Initialize a new list
 * @param self Pointer to list pointer to initialize
 * @return RET_OK on success, RET_FAIL on allocation failure
 */
int8_t ll_list_init(ll_list_t **self)
{
	if (!self) return RET_FAIL;
	ll_list_t *list = (ll_list_t*)calloc(1, sizeof(ll_list_t));
	if (!list) return RET_FAIL;
	*self = list;
	return RET_OK;
}

/**
 * @brief Create a new node associated with a list
 * @param self Pointer to node pointer to initialize
 * @param list Pointer to list this node belongs to
 * @return 0 on success, -1 on failure
 */
int8_t ll_node_new(ll_node_t **self, ll_list_t *list)
{
	if (!self) return RET_FAIL;
	ll_node_t *node = (ll_node_t*)calloc(1, sizeof(ll_node_t));
	if (!node) return RET_FAIL;
	node->list = list;
	*self = node;
	return RET_OK;
}

/**
 * @brief Append node to tail of its associated list
 * @param self Pointer to node pointer
 * @return RET_OK on success, RET_FAIL if node or list is invalid
 * 
 * If list is empty, node becomes both head and tail.
 * Otherwise, node is linked after current tail.
 */
int8_t ll_node_tail(ll_node_t **self)
{
	if (!self || !(*self)->list) return RET_FAIL;
	if (!(*self)->list->tail)
	{
		(*self)->list->tail = *self;
		(*self)->list->head = *self;
	}
	else
	{
		(*self)->prev = (*self)->list->tail;
		(*self)->list->tail->next = *self;
		(*self)->list->tail = *self;
	}
	(*self)->list->size++;
		
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
int8_t ll_node_head(ll_node_t **self)
{
	if (!self || !(*self)->list) return RET_FAIL;
	if (!(*self)->list->head)
	{
		(*self)->list->head = *self;
		(*self)->list->tail = *self;
	}
	else
	{
		(*self)->next = (*self)->list->head;
		(*self)->list->head->prev = *self;
		(*self)->list->head = *self;
	}
	(*self)->list->size++;

	return RET_OK;
}

/**
 * @brief Remove and free a node from its list
 * @param self Pointer to node pointer to delete
 * @return RET_OK on success, RET_FAIL if parameters are invalid
 * 
 * Updates list head/tail pointers and neighboring nodes as needed.
 * Decrements list size and sets pointer to NULL after freeing.
 */
int8_t ll_node_delete(ll_node_t **self)
{
	if (!self || !(*self) || !(*self)->list) return RET_FAIL;
	if (!(*self)->prev)
	{
		(*self)->list->head = (*self)->next;
	}
    else
	{
		(*self)->prev->next = (*self)->next;
	}
	
	if (!(*self)->next)
	{	
		(*self)->list->tail = (*self)->prev;
	}
	else
	{	
		(*self)->next->prev = (*self)->prev;
	}
	(*self)->list->size--;
	free(*self);	
	*self = NULL;

	return RET_OK;
}

/**
 * @brief Free entire list and all its nodes
 * @param self Pointer to list pointer to dispose
 * @return RET_OK on success, RET_FAIL if self pointer is NULL
 * 
 * Iterates through all nodes and frees them before freeing the list.
 * Returns RET_OK without error if list is already NULL.
 */
int8_t ll_list_dispose(ll_list_t **self)
{
	if (!self) return RET_FAIL;
	if (!(*self)) return RET_OK;
	ll_node_t *node = (*self)->head;
	while (node)
	{
		ll_node_t *next = node->next;
		free(node);
		node = next;
	}
	free(*self);
	*self = NULL;

	return RET_OK;
}




