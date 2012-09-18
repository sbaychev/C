#include <stdio.h>
#include <malloc.h> //modify the behavior of malloc, realloc, and free by specifying appropriate hook functions
#include <string.h>
#include "windows.h"
#define NAME_LENGTH 12
#define LINE 80

struct student
{
	int facNum;
	char firstName [NAME_LENGTH + 1];
	char secondName [NAME_LENGTH + 1]; 
	char thirdName [NAME_LENGTH + 1]; 
	int groupNum; 
	double markOne;
	double markTwo; 
	double markThree;
	double markFour;
	double avgGrade;
};typedef struct student BODY;
struct List
{
BODY body;
struct List *pNext;
};typedef struct List LIST;

LIST *insertBegin(LIST *pFirst, BODY newBody);
int enterBody(BODY *ps, int groupNumf, int facNumF, LIST **pFirst);
int duplFacNum (int stuID, LIST **pFirst);
void print(LIST *pFirst);
int printBody(BODY s);
int writeEl(LIST *pL, FILE *pF);
int readEl(BODY *pB, FILE *pF);
double subjectAvg(LIST **pFirst, int numStudents, int times);
int countListMem(LIST **pFirst);
void removeList(LIST **pFirst);
LIST *delFirst(LIST *pFirst, BODY *delBody);