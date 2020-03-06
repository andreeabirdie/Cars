#include<stdio.h>
#include"console.h"
#include"test.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main() {
	testRun();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}