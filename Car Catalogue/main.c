#include "myFunc.h"
#include <stdlib.h>
#include "windows.h"

int main()
{
LIST *pFirst = NULL, *p;
int res, i, mode, c, t;
double average = 0;
FILE *pOut = NULL, *pIn = NULL;
char Fname[]="Car_List_bin.dat";
BODY car;
char carIDnum [MIN_LENGTH+1], carBran [MAX_LENGTH+1];
char *menu[] = {"USED CAR DEALERSHIP CATALOGUE\n\tSUPPORT DATA MENU",
"1-Enter data for a new car",
"2-Write the data into a binary file",
"3-Read the data from a binary file",
"4-Display all available cars",
"5-Delete a car by a car identification number",
"6-Search and Display available cars by a specified brand",
"7-Display all cars from a speciffic brand that have a price\nlarger than the average for the brand",
"8-Destroy the car data and Exit"};

do
{ system("cls");
for(i=0; i < 9; i++)
printf("\n%s\n",menu[i]);
do
{ 
fflush(stdin);
printf ("\n\nChoose mode[1-8]: ");
res = scanf("%d", &mode);
}while(res !=1);
	switch(mode)
	{
		case 1: //data entry from the keyboard
		for(i = 0; i < LOOPS; i++)
		{
			res = enterBody(&car);
			if (res != 1 ) //the function returns 0 or 1
			{
			printf("\nError in initialization %d!\n", res);
			break;
			}
			p = insertBegin(pFirst, car);
			if(p == NULL)
			{
			printf("\n\nNot enough memory!\n");
			break;
			}
			pFirst = p;
		}
		system("pause");
		break;
		case 2: // openning the file and writing on it the list
		{				
			if (pFirst == NULL)
			{	printf("\nThe CAR CATALOGUE is Empty, there are no car records to be saved!\n");system("pause");break;}
			pOut = fopen(Fname, "wb");
			if(pOut == NULL)
			{ printf("\nCan't open file for writing!\n");
			  break;
			}
			for(p = pFirst; p != NULL ; p = p->pNext)
			{
				res = writeEl(p, pOut);
				if(res != 1)
				{   
					printf("\nWriting error %d !\n\n", res);
					break;
				}
			}
			fclose(pOut);
			removeList(&pFirst);
			printf("\nThe Catalogue data has been recorded on the Car_List_bin.dat file\n");
		}
		system("pause");
		break;
		case 3: // openning the file and reading the list
		{
		pIn = fopen(Fname, "rb");
		if( pIn == NULL)
		{
			printf("\nCan't open file for reading!\n");
			break;
		}
			do
			{
				res = readEl(&car, pIn);
				if (res != 1 && res != -4 )
				{
				printf("\nReading error %d !\n", res);
				break;
				}
				if (res != -4)
				{   p = insertBegin(pFirst, car);
					if ( p == NULL )
					{ printf("\nNot enough memory!\n");
					  break;
					}
				pFirst = p;
				}
			}while(res == 1);
		fclose(pIn);
		printf("\nThe file has been read and the catalogue is available for Display via Option 4.\n");
		}
		system("pause");
		break;
		case 4: // Displaying all available cars on the screen
		if (pFirst!=NULL)
		{
			printf("\nCarID:     Color:               EngineSize: Brand:               Price:\n");
			print(pFirst);
		}
		else
			printf("\nThe CAR CATALOGUE is Empty, there are no cars to be Displayed!\n");
		system("pause");
		break;
		case 5:
			if (pFirst == NULL)
			{	printf("\nThe CAR CATALOGUE is Empty, there are no cars to be deleted!!\n");system("pause");break;}
			do{
				fflush(stdin);
				printf("\nDelete a car by entering carID|It's an alphameric sequence of upto 10 symbols|: "); 
				if(gets(carIDnum) == NULL)//the Ctrl/Z combination
				{
					printf("Error in initialization!\n");
					break;
				}
				if(carIDnum[0] == '\0')//if nothing has been entered
				{
					printf("\nError, nothing has been entered, try again!\n");
					break;
				}
				else
				{
					delByCarID(&pFirst, carIDnum);
				}

			 }while( strlen(carIDnum) != MIN_LENGTH );
		system("pause");
		break;
		case 6: 
		if (pFirst == NULL)
		{	printf("\nThe CAR CATALOGUE is Empty, there are no cars to be searched/ displayed!\n");system("pause");break;}
		do{
			fflush(stdin);
			printf("\nSearch and Display all cars by a specified by you car brand |Character set of up to 20 symbols|: "); 
			if(gets(carBran) == NULL)//the Ctrl/Z combination
			{
				printf("\nError in initialization!\n");
				break;
			}
			if(carBran[0] == '\0')//if nothing has been entered
			{
				printf("\nError, nothing has been entered, try again!\n");
				break;
			}
			else
			{
				displByBrand(carBran, &pFirst);
			}
		}while( !( strlen(carBran) < MAX_LENGTH && strlen(carBran) > 0 ) );
		system("pause");
		break;
		case 7:
		if (pFirst == NULL)
		{	printf("\nThe CAR CATALOGUE is Empty, there are no cars to be searched/ displayed!\n");system("pause");break;}
		do{
			fflush(stdin);
			printf("\nEnter a car brand |Character set of up to 20 symbols|: "); 
			if(gets(carBran) == NULL)//the Ctrl/Z combination
			{
				printf("\nError in initialization!\n");
				break;
			}
			if(carBran[0] == '\0')//if nothing has been entered
			{
				printf("\nError, nothing has been entered, try again!\n");
				break;
			}
			else
			{
				average = brandAvg(&pFirst, carBran);
				if(average != average){ printf("\n\nThe car brand you have entered is NOT in the CAR CATALOGUE!\n\n"); break;}
				printf("\nThe Average Car Price for brand %s is: %f\n",carBran ,average);
				displAllGAvgForBrand(&pFirst, carBran, average);
			}
		}while( !( strlen(carBran) < MAX_LENGTH && strlen(carBran) > 0 ) );
		system("pause");
		break;
		case 8: 
		if (pFirst!=NULL)
		removeList(&pFirst);
		printf("\nThe CAR LIST is Empty!\nProgram exiting...\n");
		break;
	default:
	printf("\nBad choice! \n");
	system("pause");
	}
	}while(mode != 8); // eight because the list gets destroyed and we exit the program
	return 0;
	}