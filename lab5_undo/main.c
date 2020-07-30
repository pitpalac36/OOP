#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 
#include "ui.h"

int main()
{
	testAll();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}
//buna