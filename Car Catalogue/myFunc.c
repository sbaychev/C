#include "myFunc.h"
#include "windows.h"
/******************************************FUNCTIONS ***********************************************************/

/* Instead of holding a pointer to the record, it holds a pointer to the pointer that points to it - 
using a double indirection. It enables to both modify the pointer to the record and to 
modify the record without keeping track of the previous node.*/
void delByCarID(LIST **pFirst, char *carID)
{
	LIST **current;
	LIST *pNext;
	for (current = pFirst, pNext = (*current)->pNext; *current; current = &(*current)->pNext, pNext = (*current)->pNext)
	{
		if(strcmp((*current)->body.carID, carID) == 0)
		{
			free (*current);
			*current = pNext;
			printf("\nThe car with ID:%s has been deleted!\n", carID);
			break;
		}
		if(pNext == NULL)
		{ 
			printf("\nThe car with ID: %s has not been found and is NOT deleted!\n", carID);
			break;
		}
	}
}
/* It releases the memory reserved by the list. It gets the beginning of the list
via a pointer to the beginning of the list pFirst. */
void removeList(LIST **pFirst)
{
	BODY first;
	while(*pFirst != NULL)
	*pFirst = delFirst(*pFirst, &first);
}
//================================================================================
/* Deletes an element at the beginning of the list. Returns the data of deleted element
via the delBody pointer and a pointerto the beginning of the list or NULL if unsuccesful */
LIST *delFirst(LIST *pFirst, BODY *delBody)
{	if (pFirst == NULL)
	{ printf("Empty list!\n");
	return NULL;
	}
	else
	{ LIST *p; // temp link
	*delBody = pFirst->body; // saves the data
	p = pFirst->pNext; // it points the link to the second element
	if(p != NULL)
	free (pFirst); // releases the alocated mem
	pFirst = p; // it points the beginning to the link
	return pFirst;
	}
}
//================================================================================
/* Saves the data of an element from a list that the pL pointer points to, into a binary file 
with a pointer pF. Returns a flag: 1 (succesful save),
-1 (zero pointer to the data), -2(zero pointer to the file), -3 (Error upon a save into the file). */
int writeEl(LIST *pL, FILE *pF)
{
	int res;
	if (pL == NULL) return -1;
	if (pF == NULL) return -2;
	res = fwrite(&(pL->body), sizeof(BODY), 1, pF);
	if (res == 1)
	return 1; // Success
	else
	return -3; // Error upon a save into the file
}
//================================================================================
/*Reads the data from a binary file with a pF pointer. Returns data via the pointer pB and flag: 1 (successful reading),
-1 (zero pointer to the data), -2 (zero pointer to the file), -3 (Error upon reading from the file),
-4 (end of File has been reached). */
int readEl(BODY *pB, FILE *pF)
{
int res;
if (pB == NULL) return -1;
if (pF == NULL) return -2;
res = fread(pB, sizeof(BODY), 1, pF);
	if (res == 1) return 1; // Success
		else 
		{
		if (feof(pF) ) return -4; // End of File has been reached
		return -3; // Error upon reading from the file
		} 
}
//================================================================================
/* Includes element with data newBody at the beginning of pFirst in the list.
Returns a pointer of the list's beginning or NULL upon an unsuccessful operation */
LIST *insertBegin(LIST *pFirst, BODY newBody)
{
	LIST *p;
	p = (LIST *)malloc(sizeof(LIST)); // saves a mem location
	if (p == NULL)
	{ printf("\nError! There is not enough memory!\n");
	return NULL;
	}
	else
	{ p->body = newBody; // saves the data into the new element
	p->pNext = pFirst;	// points the element at the beginning
	pFirst = p;		   // sets the beginning at the new element
	return p;
	}
}
//================================================================================
/* The enterying function for cars. It does the car input into a list
via a pointer ps and flag: 0 (error upon data entry), 1 (correct data entry). */
int enterBody(BODY *ps)
{ 
  char carIDnum [MIN_LENGTH+1];
  int res, c, t;
  if(ps == NULL)
  return 0;
  memset(ps, 0, sizeof(BODY));

	do
	{
		fflush(stdin);
		printf("\nCar ID |It is an alphameric sequence of 10 symbols|: "); 
		if(gets(ps->carID) == NULL)
		{//the Ctrl/Z combination
			return 0;
		}
		if(ps->carID[0] == '\0')
		{//if nothing has been entered
			printf("\nError, nothing has been entered, try again!!\n");
			return 0;
		}
	}while( strlen(ps->carID) != MIN_LENGTH );

	fflush(stdin);
		printf("\nCar color |Character set of up to 20 symbols|: ");
		if(gets(ps->color) == NULL)
		return 0; // CTRL/Z has been pressed
		if(ps->color[0] == '\0')
		{//if nothing has been entered
			printf("\nError, nothing has been entered, try again\n"); 
			return 0;
		}
		if(strlen(ps->color) > MAX_LENGTH)
		ps->color[MAX_LENGTH] = '\0';

	do
	{ 
		fflush(stdin);
		printf("\nCar Engine Size |A real number up to 100|: ");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); return 0;}
		if ( c == EOF ){ ungetc(c, stdin); return 0;}
		ungetc(c, stdin);
		scanf("%f", &(ps->carEngineSize));
		}while( (ps->carEngineSize < 1 || ps->carEngineSize > 100) & !isdigit(ps->carEngineSize) );

	fflush(stdin);
	printf("\nCar Brand |Character set of up to 20 symbols|: ");
	if(gets(ps->carBrand) == NULL)
	return 0; // CTRL/Z has been pressed
	if(ps->carBrand[0] == '\0')
	{//if nothing has been entered
		printf("\nError, nothing has been entered, try again!\n"); 
		return 0;
	}
	if(strlen(ps->carBrand) > MAX_LENGTH)
	ps->carBrand[MAX_LENGTH] = '\0';

	do
	{ 
	fflush(stdin);
	printf("\nCar Price |A real number up to 10,000,000|: ");
	c = getchar();
	if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!\n"); return 0;}
	if ( c == EOF ){ ungetc(c, stdin); return 0;}
	ungetc(c, stdin);
	scanf("%lf", &(ps->carPrice));
	}
	while(ps->carPrice < 1 || ps->carPrice >10000000);
return 1;
}
//================================================================================
/* Prints out the elements of list that has a pointer start pFirst. */
void print(LIST *pFirst)
{
	int res;
	if(pFirst==NULL)
	printf("\nEmpty catalogue!\n");
	else
	{	LIST *p;
		p=pFirst;
		while(p!=NULL || res == 0)
		{
			res = printBody(p->body);
			p=p->pNext;
		}
		printf("\n");
	}
}
//================================================================================
/* Displays the Car Data on the Screen.
Returns a flag: 0 (error upon print), 1 (successful operation). */
int printBody(BODY s)
{
	int res;
	fflush(stdin);
	res = printf("%-11s%-21s%-12.3f%-21s%-8.5f\n", s.carID, s.color, s.carEngineSize, s.carBrand, s.carPrice);
	if(res < 0) return 0;
	else return 1;
}
//===============================================================================
void displByBrand(char *carBrand, LIST **pFirst)
{
	LIST **current;
	LIST *pNext;
	int t;
	printf("\nCarID:     Color:               EngineSize: Brand:               Price:\n");
	for (current = pFirst, pNext = (*current)->pNext; *current; current = &(*current)->pNext, pNext = (*current)->pNext)
	{
		if(strcmp((*current)->body.carBrand, carBrand) == 0)
		{
			t = printBrand(*current);if (t == 0) {return;}
			
		}
		if(pNext == NULL)
		{
			printf("\n\nEither the car brand you have entered is NOT in the Car Catalogue or the above\nis ALL of them!\n\n");
			return;
		}
	}
	return;
}
//===============================================================================
int printBrand(LIST *pFirst)
{
	LIST *t;
	int res;
	t=pFirst;
	res = printBody((t)->body);
	t = (t)->pNext;
	if (res == 0){return 0;}
}
//===============================================================================
void displAllGAvgForBrand(LIST **pFirst, char *carBrand, double average)
{
	LIST **current;
	LIST *pNext; int t;
	printf("\nCarID:     Color:               EngineSize: Brand:               Price:\n");
	for (current = pFirst, pNext = (*current)->pNext; *current; current = &(*current)->pNext, pNext = (*current)->pNext)
	{
		if( ( strcmp((*current)->body.carBrand, carBrand) ) == 0)
		{
			if((*current)->body.carPrice > average)
			{
				t = printBrand(*current); if(t == 0) {return;}
			}
		}
		if(pNext == NULL)
		{
			return;
		}
	}
}
//========================================================================================================================
double brandAvg(LIST **pFirst, char *carBrand)
{
	LIST **current;
	LIST *pNext;
	int count = 0;
	double sum = 0, avg = 0;
	for (current = pFirst, pNext = (*current)->pNext; *current; current = &(*current)->pNext, pNext = (*current)->pNext)
	{
		if( ( strcmp( (*current)->body.carBrand, carBrand ) ) == 0)
		{
			++count;
			sum += ((*current)->body.carPrice);
		}
		if(pNext == NULL)
		{			
				avg = sum/(double)count;
				return avg;
		}
	}
}