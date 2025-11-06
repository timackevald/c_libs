#include "ll.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Application structure that composes a linked list.
 * Composition: Application HAS-A list.
 * The list is embedded directly (memory managed by parent).
 */
struct application
{
	struct ll_list my_list; /* Embedded list object */
};

/**
 * @brief Initialize application and its composed objects.
 * Clear ownership: application is responsible for list lifecycle.
 */
int8_t application_init(struct application *self)
{
	if (!self) return RET_FAIL;
	/* Initialize the embedded list */
	return ll_list_init(&self->my_list);
}

/**
 * @brief Deinitialize application and cleanup resources.
 */
int8_t application_deinit(struct application *self)
{
	if (!self) return RET_FAIL;	
	/* Deinitialize the embedded list */
	return ll_list_deinit(&self->my_list);
}

/**
 * @brief Print all nodes in the list.
 */
void application_print_list(struct application *self)
{
	printf("List size: %u\n", self->my_list.size);
	struct ll_node *node = self->my_list.head;
	int index = 0;
	while (node)
	{
		printf("  Node %d at %p\n", index++, (void*)node);
		node = node->next;
	}
}

int main(void)
{
	/* 1. Create application instance (stack allocated) */
	struct application app;
	/* 2. Initialize application (and its embedded list) */
	if (application_init(&app) != RET_OK)
	{
		printf("Failed to initialize application\n");
		return 1;
	}	
	/* 3. Create some nodes (heap allocated for flexibility) */
	struct ll_node *node1 = malloc(sizeof(struct ll_node));
	struct ll_node *node2 = malloc(sizeof(struct ll_node));
	struct ll_node *node3 = malloc(sizeof(struct ll_node));	
	/* 4. Initialize nodes (associate with list) */
	ll_node_init(node1, &app.my_list);
	ll_node_init(node2, &app.my_list);
	ll_node_init(node3, &app.my_list);	
	/* 5. Add nodes to list */
	printf("Adding nodes...\n");
	ll_list_append(&app.my_list, node1);
	ll_list_append(&app.my_list, node2);
	ll_list_prepend(&app.my_list, node3);  /* node3 goes to head */	
	application_print_list(&app);	
	/* 6. Remove a node */
	printf("\nRemoving middle node...\n");
	ll_list_remove(&app.my_list, node2);
	free(node2);  /* We removed it, so we free it */
	application_print_list(&app);	
	/* 7. Cleanup: deinit will free remaining nodes */
	printf("\nCleaning up...\n");
	application_deinit(&app);	
	printf("Done!\n");
	
	return 0;
}
