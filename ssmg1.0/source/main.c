/*
 * SSMG - Smallest Simplest Maze Generator
 * -----------------------------------------------------------------------
 * This code is offered as freeware.  Created way back in elementary
 * school. Do as you please with the code, but give credits
 * to author and http://www.edepot.com/algorithm.html
 * Copyright (c) 2005 Po-Han Lin <POHANLIN@GMAIL.COM>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <stdlib.h>

PSP_MODULE_INFO("SSMG", 0x1000, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

#define WIDTH_LINES 67 
#define HEIGHT_LINES 33

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();

/////////////////////////
//// BEGIN MAZE ALGORITHM
/////////////////////////
	int x,y;
	for (x=0;x<HEIGHT_LINES;++x) {
		for (y=0;y<WIDTH_LINES;++y) pspDebugScreenPrintf("%c",rand()%2?'/':'\\');
		pspDebugScreenPrintf("\n");
	}
///////////////////////
//// END MAZE ALGORITHM
///////////////////////
	
	sceKernelExitDeleteThread(0);

	return 0;
}
