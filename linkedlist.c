

typedef struct linkedlist {
	int data;
	struct linkedlist *link;
}linkedlist;
void tailinsert(linkedlist **first, int item);    //꼬리에 삽입할때
void insert(linkedlist** first, linkedlist * x, int a);   //특정 인댁스 뒤에 삽입할때
void printing(linkedlist *first, FILE *fp);
void delete(linkedlist **first, linkedlist *trail, linkedlist *x);  // trail:삭제하기 이전  삭제할때
linkedlist* searching(linkedlist* first, int data);  //특정 노드찾는버
void free(linkedlist* first);   //연결리스트 해제





void insert(linkedlist** first, linkedlist * x, int a)     //특정 인댁스 뒤에 삽입
{
	linkedlist * temp;
	temp = (linkedlist *)malloc(sizeof(linkedlist)); //listnode 대신에 *temp가능?
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
void tailinsert(linkedlist **first, int item) {   //꼬리에 삽입
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

void printing(linkedlist *first, FILE *fp)     //파일에 출력하는 함수
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
	return curr; //NULL이 반환됨
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