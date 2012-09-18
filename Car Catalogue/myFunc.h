#include <stdio.h>
#include <malloc.h> //modify the behavior of malloc, realloc, and free by specifying appropriate hook functions
#include "windows.h"
#define LOOPS 2
#define MAX_LENGTH 20
#define MIN_LENGTH 10
struct car
{
char carID[MIN_LENGTH+1];//10 symbols
char color[MAX_LENGTH+1];//20 symbols
float carEngineSize;
char carBrand[MAX_LENGTH+1];
double carPrice;
};
typedef struct car BODY;
struct List
{
BODY body;
struct List *pNext;
};
typedef struct List LIST;

void delByCarID(LIST **pFirst, char *carID);
void removeList(LIST **pFirst);
LIST *delFirst(LIST *pFirst, BODY *delBody);
int writeEl( LIST *pL, FILE *pF);
int readEl( BODY *pB, FILE *pF);
LIST *insertBegin(LIST *pFirst, BODY newBody);
int enterBody(BODY *ps);
void print(LIST *pFirst);
int printBody(BODY s);
void displByBrand(char *carBrand, LIST **pFirst);
int printBrand(LIST *pFirst);
void displAllGAvgForBrand(LIST **pFirst, char *carBrand, double average);
double brandAvg(LIST **pFirst, char *carBrand);