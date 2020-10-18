#include <myhead.h>

//初始化内核链表
klist *init_list()
{
	klist *head = malloc(sizeof(klist));
	if(head)
		INIT_LIST_HEAD(&(head->mylist));
	return head;
}

//新建新节点
klist *new_node(char *path)
{
	klist *new = malloc(sizeof(klist));
	if(new)
	{
		strcpy(new->path,path);
		INIT_LIST_HEAD(&(new->mylist));
	}
	return new;
}

//释放内核链表的所有堆空间
int free_klist(klist *head)
{
	klist *p;
	klist *n;
	list_for_each_entry_safe(p, n, &(head->mylist), mylist)
	{
		list_del(&(p->mylist));
		free(p);
	}
	list_del(&(p->mylist));
	free(p);
	return 0;
}


