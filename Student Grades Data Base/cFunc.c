#include "hFunc.h"
#include "windows.h"
/******************************************FUNCTIONS ***********************************************************/

/* The data entry function for students. It does the student input into a list
via a pointer ps and flag: 0 (error upon data entry), 1 (correct data entry - if no errors are encountered in the process). */
int enterBody(BODY *ps, int groupNumf, int facNumF, LIST **pFirst)
{ 
  int c, i = 0, k = 0, z = 0, x = 0, n = 0, m = 0, ret, fGrNum = 0;
  char strFNUM [LINE], strGrNUM [LINE], mOne[LINE], mTwo[LINE], mThree[LINE], mFour[LINE]; // making them all the standard windows
  if(ps == NULL)																		  // cmd screen buffer size, just to be sure
  return 0;
  memset(ps, 0, sizeof(BODY));

stuFacNum:
	do
	{
		fflush(stdin);
		printf("\nStudent Faculty Number |An integer value of 9 digits,NO 0 at start|: ");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); goto stuFacNum;}
		if ( c == EOF ){ ungetc(c, stdin); return 0;}
		ungetc(c, stdin);
		scanf("%s", &strFNUM);
		if(strlen(strFNUM) > LINE)
		strFNUM[LINE] = '\0';
	}while ( (strlen(strFNUM) > 9) || (strlen(strFNUM) < 9) );
	if(strFNUM [0] == '0'){printf("\nError, you can NOT have a ZERO -> 0 entered as a \nbeginning of this set of integer values, try again!!\n"); goto stuFacNum;}
	for (z; z < 9; z++)
	{
		if( ispunct(strFNUM [z]) )
		{
			printf("\nError, you can NOT have a punctuation character entered in this set\nof integer values, try again!!\n"); goto stuFacNum;
		}
	}
	for (x; x < 9; x++)
	{
		if( isalpha(strFNUM [x]) )
		{
			printf("\nError, you can NOT have an alphabetic character entered in this set\nof integer values, try again!!\n"); goto stuFacNum;
		}
	}
	for (i; i < 9; i++)
	{
		if ( !isdigit(strFNUM [i]) )
		{
			printf("\nError, you have not entered a set of integer values, try again!!\n"); goto stuFacNum;
		}
	}
	strFNUM[10] = '\0';
	ps->facNum = atoi (strFNUM);
	
	if (facNumF == 0){ ret = duplFacNum(ps->facNum, pFirst); if (ret == 1) { goto stuFacNum; } if(ret == 0){ goto stuFirstName;} }

stuFirstName:
	fflush(stdin);
	printf("\nStudent, First Name |Character set of up to 12 symbols|: ");
	if(gets(ps->firstName) == NULL)
	return 0; // CTRL/Z has been pressed
	if(ps->firstName[0] == '\0')
	{//if nothing has been entered
		printf("\nError, nothing has been entered, try again\n"); 
		return 0;
	}
	if(strlen(ps->firstName) > NAME_LENGTH)
	ps->firstName[NAME_LENGTH] = '\0';

	fflush(stdin);
	printf("\nStudent, Second Name |Character set of up to 12 symbols|: ");
	if(gets(ps->secondName) == NULL)
	return 0; // CTRL/Z has been pressed
	if(ps->secondName[0] == '\0')
	{//if nothing has been entered
		printf("\nError, nothing has been entered, try again\n"); 
		return 0;
	}
	if(strlen(ps->secondName) > NAME_LENGTH)
	ps->secondName[NAME_LENGTH] = '\0';

	fflush(stdin);
	printf("\nStudent, Third Name |Character set of up to 12 symbols|: ");
	if(gets(ps->thirdName) == NULL)
	return 0; // CTRL/Z has been pressed
	if(ps->thirdName[0] == '\0')
	{//if nothing has been entered
		printf("\nError, nothing has been entered, try again\n"); 
		return 0;
	}
	if(strlen(ps->thirdName) > NAME_LENGTH)
	ps->thirdName[NAME_LENGTH] = '\0';

stuGroupNum:
	do
	{
		fflush(stdin);
		printf("\nStudent Group Number |It is an integer value of 3 digits,NO 0 at start|: "); 
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); goto stuGroupNum;}
		if ( c == EOF ){ ungetc(c, stdin); return 0;}
		ungetc(c, stdin);
		scanf("%s", &strGrNUM);
		if(strlen(strGrNUM) > LINE)
		strGrNUM[LINE] = '\0';
	}while ( strlen(strGrNUM) > 3 || strlen(strGrNUM) < 3);
	if(strGrNUM [0] == '0'){printf("\nError, you can NOT have a ZERO -> 0 entered as a \nbeginning of this set of integer values, try again!!\n"); goto stuGroupNum;}
	for (n; n < 3; n++)
	{
		if( ispunct(strGrNUM [n]) )
		{
			printf("\nError, you can NOT have a punctuation character entered in this set\nof integer values, try again!!\n"); goto stuGroupNum;
		}
	}
	for (m; m < 3; m++)
	{
		if( isalpha(strGrNUM [m]) )
		{
			printf("\nError, you can NOT have an alphabetic character entered in this set\nof integer values, try again!!\n"); goto stuGroupNum;
		}
	}
	for (k; k < 3; k++)
	{
		if ( !isdigit(strGrNUM [k]) )
		{
			printf("\nError, you have not entered a set of integer values, try again!!\n"); goto stuGroupNum;
		}
	}
	strGrNUM[4] = '\0';
	ps->groupNum = atoi (strGrNUM);
	if (groupNumf != 0){ if( (ps->groupNum != groupNumf) ) {printf("\nError, you have not entered the correct Group Number %d, try again!!\n", groupNumf); goto stuGroupNum; } }


marOne:
		do
		{
		fflush(stdin);
		printf("\nEnter a Student Grade for Subject A |A real or an integer number from 2.00 to 6.00|: ");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); goto marOne;}
		if ( c == EOF ){ ungetc(c, stdin); return 0;}
		ungetc(c, stdin);		
		scanf("%s", &mOne);
		if(strlen(mOne) > LINE)
		mOne[LINE] = '\0';
		}while ( strlen(mOne) != 1 );
		if ( !isdigit(mOne[0]) ){ printf("\nError, you have not entered a digit, try again!!\n"); goto marOne; }
		ps->markOne = atof(mOne);
	if( (ps->markOne < 2 || ps->markOne > 6) ){ printf("\nError, you have not entered an integer number from 2.00 to 6.00, try again!!\n"); goto marOne;}
	
marTwo:
		do
		{
		fflush(stdin);
		printf("\nEnter a Student Grade for Subject B |A real or an integer number from 2.00 to 6.00|: ");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); goto marTwo;}
		if ( c == EOF ){ ungetc(c, stdin); return 0;}
		ungetc(c, stdin);
		scanf("%s", &mTwo);
		if(strlen(mTwo) > LINE)
		mTwo[LINE] = '\0';
		}while ( strlen(mTwo) != 1 );
		if ( !isdigit(mTwo[0]) ){ printf("\nError, you have not entered a digit, try again!!\n"); goto marTwo; }
		ps->markTwo = atof(mTwo);
	if( (ps->markTwo < 2 || ps->markTwo > 6) ){ printf("\nError, you have not entered an integer number from 2.00 to 6.00, try again!!\n"); goto marTwo; }
	
marThree:
		do
		{
		fflush(stdin);
		printf("\nEnter a Student Grade for Subject C |A real or an integer number from 2.00 to 6.00|: ");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); goto marThree;}
		if ( c == EOF ){ ungetc(c, stdin); return 0;}
		ungetc(c, stdin);
		scanf("%s", &mThree);
		if(strlen(mThree) > LINE)
		mThree[LINE] = '\0';
		}while ( strlen(mThree) != 1 );
		if ( !isdigit(mThree[0]) ){ printf("\nError, you have not entered a digit, try again!!\n"); goto marThree; }
		ps->markThree = atof(mThree);
		if( (ps->markThree < 2 || ps->markThree > 6) ){ printf("\nError, you have not entered an integer number from 2.00 to 6.00, try again!!\n"); goto marThree; }

marFour:
		do
		{
		fflush(stdin);
		printf("\nEnter a Student Grade for Subject D |A real or an integer number from 2.00 to 6.00|: ");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); goto marFour;}
		if ( c == EOF ){ ungetc(c, stdin); return 0;}
		ungetc(c, stdin);
		scanf("%s", &mFour);
		if(strlen(mFour) > LINE)
		mFour[LINE] = '\0';
		}while ( strlen(mFour) != 1 );
		if ( !isdigit(mFour[0]) ){ printf("\nError, you have not entered a digit, try again!!\n"); goto marFour; }
		ps->markFour = atof(mFour);
	if( (ps->markFour < 2 || ps->markFour > 6) ){ printf("\nError, you have not entered an integer number from 2.00 to 6.00, try again!!\n"); goto marFour; }

	ps->avgGrade = (ps->markOne + ps->markTwo + ps->markThree + ps->markFour)/4;
return 1;
}
//================================================================================================================
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
//================================================================================================================
/* Searches the student list members for duplicate Student Faculty members, if true returns 1, else just breaks the search and returns 0 */
int duplFacNum (int stuID, LIST **pFirst)
{
	LIST **current;
	LIST *pNext;
	for (current = pFirst, pNext = (*current)->pNext; *current; current = &(*current)->pNext, pNext = (*current)->pNext)
	{
		if((*current)->body.facNum == stuID)
		{
			printf("\nThere is already a student with Faculty Number: %d, try again!!\n", stuID);
			return 1;
		}
				if(pNext == NULL)
		{			
			return 0;
		}
	}
}
//================================================================================================================
/* Prints out the elements of list that has a pointer start pFirst. */
void print(LIST *pFirst)
{
	int res;
	LIST *p;
	p=pFirst;
	while(p!=NULL || res == 0)
	{
		res = printBody(p->body);
		p=p->pNext;
	}
	printf("\n");
}
//=================================================================================================================================
/* Displays the Student Data on the Screen.
Returns a flag: 0 (error upon print), 1 (successful operation). */
int printBody(BODY s)
{
	int res;
	fflush(stdin);
	res = printf("%d %-12s %-12s %-12s %d %-.2f %-.2f %-.2f %-.2f %.4lf\n", s.facNum, s.firstName, s.secondName, s.thirdName, 
														s.groupNum, s.markOne, s.markTwo, s.markThree, s.markFour, s.avgGrade);
	if(res < 0) return 0;
	else return 1;
}
//================================================================================================================================
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
//====================================================================================================================
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
//====================================================================================================================
/* Calculates the Grade Point Average per subject via a for cycle that goes through the list of student members*/
double subjectAvg(LIST **pFirst, int numStudents, int times)
{
	LIST **current;
	LIST *pNext;
	double sum = 0, avg = 0;
	for (current = pFirst, pNext = (*current)->pNext; *current; current = &(*current)->pNext, pNext = (*current)->pNext)
	{
		if( times == 0 )
		{
			sum += ((*current)->body.markOne);
		}
		if( times == 1 )
		{
			sum += ((*current)->body.markTwo);
		}
		if( times == 2 )
		{
			sum += ((*current)->body.markThree);
		}
		if( times == 3 )
		{
			sum += ((*current)->body.markFour);
		}
		if(pNext == NULL)
		{			
				avg = sum/(double)numStudents;
				return avg;
		}
	}
}
//=======================================================================================================================
/* A simple function that returns the number of students; it uses a for cycle to go through the list*/
int countListMem(LIST **pFirst)
{
	LIST **current;
	LIST *pNext;
	int count = 0;
	for (current = pFirst, pNext = (*current)->pNext; *current; current = &(*current)->pNext, pNext = (*current)->pNext)
	{
		++count;
		if(pNext == NULL)
		{			
				return count;
		}
	}
}
//=====================================================================================================================
/* It releases the memory reserved by the list. It gets the beginning of the list
via a pointer to the beginning of the list pFirst. */
void removeList(LIST **pFirst)
{
	BODY first;
	while(*pFirst != NULL)
	*pFirst = delFirst(*pFirst, &first);
}
//==================================================================================================
/* Deletes an element at the beginning of the list. Returns the data of deleted element
via the delBody pointer and a pointer to the beginning of the list or NULL if unsuccesful */
LIST *delFirst(LIST *pFirst, BODY *delBody)
{	if (pFirst == NULL)
	{ printf("\nEmpty list!\n");
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