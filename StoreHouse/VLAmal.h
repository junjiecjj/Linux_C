

/************************************************************************

*************************************************************************/


#ifndef _VLA_CJJ
#define _VLA_CJJ



#include <stdio.h>
#include <stdlib.h>
#include  "Utility.h"

#define MONTHS 12
#define LEN 10

extern int *GlobalPoint;

extern const int days[MONTHS];
extern   int *valpi;
// extern static int *valpi;

int   *MallocAndReturnLocalPoint(void);
void  UseLocalPoint(void);
void  FreeLocalPoint(int *LocalPoint);

void InitStaticMemory(void);
void ChangeStaticMem(void);
void FreeStaticMem(void);


void DisplayMonth(void);



#endif  //_VLA_CJJ