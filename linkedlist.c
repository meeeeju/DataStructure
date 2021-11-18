

typedef struct linkedlist {
	int data;
	struct linkedlist *link;
}linkedlist;
void tailinsert(linkedlist **first, int item);    //������ �����Ҷ�
void insert(linkedlist** first, linkedlist * x, int a);   //Ư�� �δ콺 �ڿ� �����Ҷ�
void printing(linkedlist *first, FILE *fp);
void delete(linkedlist **first, linkedlist *trail, linkedlist *x);  // trail:�����ϱ� ����  �����Ҷ�
linkedlist* searching(linkedlist* first, int data);  //Ư�� ���ã�¹�
void free(linkedlist* first);   //���Ḯ��Ʈ ����





void insert(linkedlist** first, linkedlist * x, int a)     //Ư�� �δ콺 �ڿ� ����
{
	linkedlist * temp;
	temp = (linkedlist *)malloc(sizeof(linkedlist)); //listnode ��ſ� *temp����?
	temp->data = a;
	if (*first)
	{
		temp->link = x->link;
		x->link = temp;

	}
	else
	{
		temp->link = NULL;
		*first = temp;
	}
}
void tailinsert(linkedlist **first, int item) {   //������ ����
	linkedlist * node1;
	linkedlist *current;
	current = *first;
	node1 = (linkedlist *)malloc(sizeof(linkedlist));
	node1->data = item;
	node1->link = NULL;
	if (current)
	{
		while (current->link)
			current = current->link;
	}
	if (current)
		current->link = node1;
	else
		*first = node1;
}

void printing(linkedlist *first, FILE *fp)     //���Ͽ� ����ϴ� �Լ�
{
	linkedlist *current = first;
	while (current != 0)
	{
		fprintf(fp, "%3d", current->data);
		current = current->link;
	}

}

void delete(linkedlist **first, linkedlist *trail, linkedlist *x)
{
	if (trail) {
		trail->link = x->link;
	}
	else
		*first = (*first)->link;
	free(x);

}
linkedlist* searching(linkedlist* first, int data)
{
	linkedlist* curr;
	curr = first;
	while (curr)
	{
		if (curr->data == data)
		{
			return curr;
		}
		else
		{
			curr = curr->link;
		}
	}
	return curr; //NULL�� ��ȯ��
}

void free(linkedlist* first)
{
	linkedlist* curr, *prev;
	curr = first;
	while (curr)
	{
		prev = curr->link;
		free(curr);
		curr = prev;
	}
}