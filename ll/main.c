#include "ll.h"
#include <stdio.h>

int main(void)
{
	ll_list_t *list;
	if (ll_list_init(&list) != 0)
	{
		printf("Failed to create list!\n");
		return -1;
	}
	printf("Successfully created list...\n");

	size_t i;
	for (i = 0; i < 3; i++)
	{
		ll_node_t *node;
		if (ll_node_new(&node, list) != 0)
		{
			printf("Failed to create node!\n");
			return -1;
		}
		printf("Successfully created node [%zu]...\n", i);

		if (ll_node_tail(&node) != 0)
		{
			printf("Failed to add node to tail of list!\n");
			return -1;
		}
		printf("Successfully added node [%zu] to tail of list\n", i);
	}

	if (ll_list_dispose(&list) != 0)
	{
		printf("Failed to dispose of list!\n");
		return -1;
	}
	printf("Successfully disposed of list\n");
	
	return 0;
}
