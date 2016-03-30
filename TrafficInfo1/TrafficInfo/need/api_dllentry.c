/* -----------------------------------------------------------------------
 *
 * This file provides the mandatory entry point for a DLL
 * ----------------------------------------------------------------------- */ 
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL APIENTRY DllMain(HANDLE h, DWORD d,  LPVOID lpReserved)
{
    return TRUE;
}
#endif


