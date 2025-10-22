/**
 * @file ll.h
 * @brief Doubly linked list implementation
 * @author Tim Ackevald
 * @date 2025-10
 */

#ifndef __LL_H_
#define __LL_H_

#include <stdint.h>

typedef struct ll_list ll_list_t;
typedef struct ll_node ll_node_t;

/**
 * @brief Node structure for doubly linked list
 */
struct ll_node
{
	ll_list_t *list;
	ll_node_t *next;
	ll_node_t *prev;
};

/**
 * @brief List structure containing head, tail, and size
 */
struct ll_list
{
	ll_node_t *head;
	ll_node_t *tail;
	uint32_t size;
};

/**
 * @brief Initialize a new list
 */
int8_t ll_list_init(ll_list_t **self);

/**
 * @brief Create a new node associated with a list
 */
int8_t ll_node_new(ll_node_t **self, ll_list_t *list);

/**
 * @brief Append node to tail of its associated list
 */
int8_t ll_node_tail(ll_node_t **self);

/**
 * @brief Prepend node to head of its associated list
 */
int8_t ll_node_head(ll_node_t **self);

/**
 * @brief Remove and free a node from its list
 */
int8_t ll_node_delete(ll_node_t **self);

/**
 * @brief Free entire list and all its nodes
 */
int8_t ll_list_dispose(ll_list_t **self);

#endif /* __LL_H_ */
