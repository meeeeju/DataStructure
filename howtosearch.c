//1¿Â
void selction_sort(int *array1,int num)
{
	int min,i, j, temp;
	min = i;
	for (j = i + 1; j < num; j++)
	{
		if (array1[j] < array1[min])
			min = j;
	}
	temp = array1[min];
	array1[min] = array1[i];
	array1[i] = temp;

	printf("\n");

}

#define compare(x,y)(((x)<(y))?-1:((x)==(y))?0:1)
int binsearch(int list[], int sele, int left, int right)
{
	int middle, x;
	while (left <= right)
	{

		middle = (left + right) / 2;
		x = compare(list[middle], sele);
		switch (x)
		{
		case -1: left = middle + 1;
			break;

		case 0: return middle;
		case 1:
			right = middle - 1;
			//break;

		}
	}
	return -1;
}