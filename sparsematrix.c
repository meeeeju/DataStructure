#define Max 101
typedef struct {
	int col;
	int row;
	int value;
}term;
term a[Max];
term b[Max];
void createarr(term *a, int **b, int row, int col);
void fasttransp0se(term a[], term b[]);
void transpOse(term a[], term b[]);
void createarr(term *a, int **b, int row, int col)
{
	int i, j;
	int k = 1;
	a[0].row = row;
	a[0].col = col;
	for (i = 0; i < a[0].row; i++)
	{
		for (j = 0; j < a[0].col; j++)
		{
			if (b[i][j] != 0)
			{
				a[k].row = i;
				a[k].col = j;
				a[k].value = b[i][j];
				k++;
			}
		}
	}
	a[0].value = k - 1;  //elementsÀÇ °¹¼ö

}
void fasttransp0se(term a[], term b[])
{
	int *rowterms;
	int *startingPos;
	int i, j, k;
	int numterms = a[0].value;
	b[0].col = a[0].row;
	b[0].row = a[0].col;
	b[0].value = numterms;
	startingPos = (int*)calloc(a[0].col, sizeof(int));
	rowterms = (int*)calloc(a[0].col, sizeof(int));
	if (numterms)
	{

		for (i = 1; i <= a[0].value; i++)
			rowterms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i < a[0].col; i++)
			startingPos[i] = startingPos[i - 1] + rowterms[i - 1];

	}
	for (i = 1; i <= numterms; i++)
	{
		j = startingPos[a[i].col];
		b[j].row = a[i].col;
		b[j].col = a[i].row;
		b[j].value = a[i].value;
		startingPos[a[i].col]++;


	}
	free(rowterms);
	free(startingPos);
}
void transpOse(term a[], term b[])
{
	int n, j, i, currentb;
	n = a[0].value;    /*total number of matrix*/
	b[0].row = a[0].col;   /*rows in b=column in a*/
	b[0].col = a[0].row;    /*column in b=rows in a*/
	b[0].value = n;
	if (n > 0)/*check non zero matrix*/
	{
		
		currentb = 1;
		for (i = 0; i < a[0].col; i++)
		{/*transpose by the columns in a*/
			for (j = 1; j <= n; j++)
			{
				/*find elements form the current column*/
				if (a[j].col == i)
				{
					/*element is in current column,add it to b*/
					b[currentb].row = a[j].col;
					b[currentb].col = a[j].row;
					b[currentb].value = a[j].value;
					currentb++;
				}
			}
		}
	}
}