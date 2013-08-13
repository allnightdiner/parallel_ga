#ifndef FILE_LL
#define FILE_LL

struct node
{
	struct node *next;
	void *data;
};

int ll_has_next(struct node*);
struct node* ll_add(void*, struct node*);
struct node* ll_remove(struct node*);
void ll_free(struct node*);

#endif
