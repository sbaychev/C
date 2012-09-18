#include "hFunc.h"
#include <stdlib.h>
#include "windows.h"
int main()
{
	LIST *pFirst = NULL, *p;
	int res, i, mode, c, fGroupNum = 1, fGrNum = 0, fiFacNum = 1, k, o, loops, actStudC = 0 , fileStudCount = 0, flag = 0;
	double avgMarkOne = 0, avgMarkTwo = 0, avgMarkThree = 0, avgMarkFour = 0, avgMarkAll = 0;
	FILE *pOut = NULL, *pIn = NULL;
	char fOutName [30], fInName [30];
	BODY student;

	char *menu[] = {"STUDENT EXAM SESSION DATA\n    SUPPORT DATA MENU",
	"1-Enter manually the data for a new student",
	"2-Write the student data into a binary file",
	"3-Read student data from a binary file",
	"4-Display all available students' information",
	"5-Destroy the student information and Exit"};

do
{ 
	system("cls");
	for(i=0; i < 6; i++)
	printf("\n%s\n",menu[i]);
do
{ 
fflush(stdin);
printf ("\n\nChoose mode[1-5]: ");
res = scanf("%d", &mode);
}while(res !=1);
	switch(mode)
	{
		case 1: //data entry from the keyboard
		fflush(stdin);
		printf("\nEnter the number of students' information you wish to enter: ");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); system("pause"); break;}
		if ( c == EOF ){ ungetc(c, stdin); system("pause"); break;}
		ungetc(c, stdin);
		scanf("%d", &loops);
		fflush(stdin);
		for(i = 0; i < loops; i++)
		{
			system("cls");
			fflush(stdin);
			res = enterBody(&student, fGrNum, fiFacNum, &pFirst);
			if (res != 1 ) //the function returns 0 or 1
			{
				printf("\nError in initialization %d!\n", res);
				break;
			}
			if (fGroupNum == 1) {fGrNum = student.groupNum;}
			p = insertBegin(pFirst, student);
			if(p == NULL)
			{
			printf("\n\nNot enough memory!\n");
			system("pause");
			break;
			}
			pFirst = p;
			++actStudC;
			fGroupNum = 0;
			fiFacNum = 0;
		}
		if(actStudC > 0)
		{
			
			if (flag == 1){actStudC = (actStudC + fileStudCount); flag = 0;}
			for (k = 0; k < 4; k++)
			{
				if(k == 0) avgMarkOne = subjectAvg(&pFirst, actStudC, k);
				if(k == 1) avgMarkTwo = subjectAvg(&pFirst, actStudC, k);
				if(k == 2) avgMarkThree = subjectAvg(&pFirst, actStudC, k);
				if(k == 3) avgMarkFour = subjectAvg(&pFirst, actStudC, k);
			}
		avgMarkAll = (avgMarkOne + avgMarkTwo + avgMarkThree + avgMarkFour)/4;
		}
		system("pause");
		break;

		case 2: // openning the file and writing on it the list
		fflush(stdin);
		if (pFirst == NULL)
		{	printf("\nThe STUDENT EXAM SESSION DATA is Empty,\nthere is no student data to be saved!\n\n");system("pause");break;}
		printf("\nEnter the Name of the File you would like to record the data to\n|It should be an alphameric sequence of up 25 symbols ending with .dat|:\n");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); system("pause"); break;}
		if ( c == EOF ){ ungetc(c, stdin); system("pause"); break;}
		ungetc(c, stdin);
		scanf("%s", &fOutName);
		pOut = fopen(fOutName, "wb");
		if(pOut == NULL)
		{ 
			printf("\nCan't open file for writing!\n");
			system("pause");
			break;
		}
		for(p = pFirst; p != NULL ; p = p->pNext)
		{
			res = writeEl(p, pOut);
			if(res != 1)
			{   
				printf("\nWriting error %d !\n\n", res);
				system("pause");
				break;
			}
		}
		fclose(pOut);
		removeList(&pFirst);
		printf("\nThe STUDENT EXAM SESSION DATA has been recorded on the %s file\n", fOutName);
		system("pause");
		break;

		case 3: // openning the file and reading the list
		fflush(stdin);
		{
		printf("\nEnter the Name of the File you would like to read the data from\n| It should be an alphameric sequence of up 25 symbols ending with .dat |:\n");
		c = getchar();
		if ( c == '\n' ){ ungetc(c, stdin); printf("\nError, nothing has been entered, try again!!\n"); system("pause"); break;}
		if ( c == EOF ){ ungetc(c, stdin); system("pause"); break;}
		ungetc(c, stdin);
		scanf("%s", &fInName);
		pIn = fopen(fInName, "rb");
		if( pIn == NULL)
		{
			printf("\nCan't open file for reading!\n");
			system("pause");
			break;
		}
			do
			{
				res = readEl(&student, pIn);
				if (res != 1 && res != -4 )
				{
				printf("\nReading error %d !\n", res);
				system("pause");
				break;
				}
				if (res != -4)
				{   
					p = insertBegin(pFirst, student);
					if ( p == NULL )
					{ 
					  printf("\nNot enough memory!\n");
					  system("pause");
					  break;
					}
				pFirst = p;
				}
			}while(res == 1);
		fclose(pIn);
		printf("\nThe file has been read and the STUDENT EXAM SESSION DATA\nis available for Display via Option 4.\n");
		}
		fileStudCount = countListMem(&pFirst);
		flag = 1;
		system("pause");
		break;

		case 4: // Displaying all 
		fflush(stdin);
			if (pFirst!=NULL)
			{
				if(flag == 1)
				{
					for (o = 0; o < 4; o++)
					{
						if(o == 0) avgMarkOne = subjectAvg(&pFirst, fileStudCount, o);
						if(o == 1) avgMarkTwo = subjectAvg(&pFirst, fileStudCount, o);
						if(o == 2) avgMarkThree = subjectAvg(&pFirst, fileStudCount, o);
						if(o == 3) avgMarkFour = subjectAvg(&pFirst, fileStudCount, o);
					}
					avgMarkAll = (avgMarkOne + avgMarkTwo + avgMarkThree + avgMarkFour)/4;
					//flag = 0;
				}
				printf("\nRESULTS from a Winter Exam session\n\n");
				printf("FacNum:   Name,First:  Name,Second: Name,Third:  GrNum: sA: sB: sC: sD:  AvgGrd:\n");
				print(pFirst);
				printf("                                 Grade Point Average %-.2f %-.2f %-.2f %-.2f %.4lf\n", avgMarkOne, avgMarkTwo, avgMarkThree, avgMarkFour, avgMarkAll);
			}
			else
			printf("\nThe STUDENT EXAM SESSION DATA is Empty,\nthere are no student data to be Displayed!\n\n");
		system("pause");
		break;

		case 5: 
		fflush(stdin);
		if (pFirst!=NULL)
		removeList(&pFirst);
		printf("\nThe STUDENT EXAM SESSION DATA is Empty!\nProgram exiting...\n");
		break;

	default:
	printf("\nBad choice! \n");
	system("pause");
	}
	}while(mode != 5); // because the list gets destroyed and we exit the program
	return 0;
}