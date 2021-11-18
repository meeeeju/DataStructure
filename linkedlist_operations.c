typedef struct linkedlist* pointer;
typedef struct linkedlist
{
	int data;
	struct linkedlist* link;
}linkedlist;

//<일반 연결 리스트>
 pointer invert(pointer lead);   //10 20 30 40 -> 40 30 20 10
 linkedlist* concentration(linkedlist* ptr1, linkedlist* ptr2);  //ptr1 ptr2 를 붙이는 기능

 void attach(linkedlist** tail, int data);  //꼬리에 삽입시키고 꼬리는 그 다음 꼬리를 가르킴

 //<circular linkedlist>
 void insertFront(linkedlist** last, linkedlist* node);   //circular linked list에서 꼬리 앞에 삽입 (즉 젤 앞에라고말할수O)

 int length(linkedlist* last);  //circular linkedlsit에서 node의 개수를 반환


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
	(*tail)->link = temp;       //순서를 바꾸면
	//temp->prev = *tail;     //순서를 바꾸면?  상관없음
	*tail = temp;
}

