#include "DOA.h"
#include "Net.h"
#include "Time.h"


void byby(void)
{
	printf("I'm byby.....\n");
	printf("function: [%s], File Path: [%s], Line: [%d], Time: [%s] \n", __func__, __FILE__, __LINE__, GetTimeOfNow() );

	printf("function: [%s], File Path: [%s], Line: [%d], Time: [%s,%s] \n", __func__, __FILE__, __LINE__, __DATE__, __TIME__);
	printf("[%s, %s, %d], Time: %s,%s] \n", __FILE__, __func__,  __LINE__, __DATE__, __TIME__);
	hello();
}

