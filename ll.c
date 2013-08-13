#include <stdlib.h>
#include "ll.h"

int ll_has_next(struct node* ll)
{
	if(ll == NULL)
		return 0;
	else
		return 1;
}

/* adds to head of a linked list, returns new head of list*/
struct node*  ll_add(void *new_data, struct node *ll)
{
	struct node* new_head = malloc(sizeof(struct node));
	new_head->data = new_data;
	new_head->next = ll;
	return new_head;
}

/* in the name of side effects! */
struct node* ll_remove(struct node *ll)
{
	struct node *ret = ll;
	ll = ll->next;
	return ret;	
}

void ll_free(struct node* to_free)
{
	struct node* tmp = to_free;
	struct node* prev = to_free;
	while(tmp != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev->data);
		free(prev);
	}
}
