/**
 * @file ll.h
 * @brief Doubly linked list implementation
 * @author Tim Ackevald
 * @date 2025-10
 */

#ifndef __LL_H_
#define __LL_H_

#include <stdint.h>

/**
 * @brief Return code enumeration
 */

typedef enum
{
	RET_FAIL = -1,
	RET_OK   = 0,
} ll_retcode_t;

struct ll_list;

/**
 * @brief Node structure for doubly linked list
 */
struct ll_node
{
	struct ll_list *list;
	struct ll_node *next;
	struct ll_node *prev;
};

/**
 * @brief List structure containing head, tail, and size
 */
struct ll_list
{
	struct ll_node *head;
	struct ll_node *tail;
	uint32_t size;
};

/**
 * @brief Initialize a new list
 */
int8_t ll_list_init(struct ll_list *self);

/**
 * @brief Free entire list and all its nodes
 */
int8_t ll_list_deinit(struct ll_list *self);

/**
 * @brief Create a new node associated with a list
 */
int8_t ll_node_init(struct ll_node *self, struct ll_list *list);

/**
 * @brief Append node to tail of its associated list
 */
int8_t ll_list_append(struct ll_list *self, struct ll_node *node);

/**
 * @brief Prepend node to head of its associated list
 */
int8_t ll_list_prepend(struct ll_list *self, struct ll_node *node);

/**
 * @brief Remove and free a node from its list
 */
int8_t ll_list_remove(struct ll_list *self, struct ll_node *node);

#endif /* __LL_H_ */
