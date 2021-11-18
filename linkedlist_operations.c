typedef struct linkedlist* pointer;
typedef struct linkedlist
{
	int data;
	struct linkedlist* link;
}linkedlist;

//<�Ϲ� ���� ����Ʈ>
 pointer invert(pointer lead);   //10 20 30 40 -> 40 30 20 10
 linkedlist* concentration(linkedlist* ptr1, linkedlist* ptr2);  //ptr1 ptr2 �� ���̴� ���

 void attach(linkedlist** tail, int data);  //������ ���Խ�Ű�� ������ �� ���� ������ ����Ŵ

 //<circular linkedlist>
 void insertFront(linkedlist** last, linkedlist* node);   //circular linked list���� ���� �տ� ���� (�� �� �տ�����Ҽ�O)

 int length(linkedlist* last);  //circular linkedlsit���� node�� ������ ��ȯ


pointer  invert(pointer lead) 
{
	/*invert the list pointed to by lead*/
	pointer middle,trail;
	middle=NULL:
	while (lead)
	{
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;

}


linkedlist* concentration(linkedlist* ptr1, linkedlist* ptr2)
{
	linkedlist* temp;
	if (!ptr1)
		return ptr2;
	if (!ptr2)
		return ptr1;
	for (temp = ptr1; temp->link; temp = temp->link);
	temp->link = ptr2;
	return ptr1;

}

void attach(linkedlist** tail, int data)
{
	linkedlist* temp;
	temp = (linkedlist*)malloc(sizeof(*temp));
	temp->data = data;
	(*tail)->link = temp;       //������ �ٲٸ�
	//temp->prev = *tail;     //������ �ٲٸ�?  �������
	*tail = temp;
}

