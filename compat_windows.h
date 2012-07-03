#ifndef _COMPAT_WINDOWS_H
#define _COMPAT_WINDOWS_H

#include <pthread.h>

#define MAX_PATH 260
typedef unsigned long DWORD;

typedef pthread_mutex_t  CRITICAL_SECTION;

unsigned long GetCurrentDirectory(
     unsigned long nBufferLength,
     char * lpBuffer
    );

void Sleep(
     unsigned long dwMilliseconds
    );

unsigned long GetPrivateProfileString(
    const char * lpAppName,
    const char * lpKeyName,
    const char * lpDefault,
    char * lpReturnedString,
    unsigned long nSize,
    const char * lpFileName
    );


void
InitializeCriticalSection(
    pthread_mutex_t * lpCriticalSection
    );
 
void
EnterCriticalSection(
    pthread_mutex_t * lpCriticalSection
    );
    
void
LeaveCriticalSection(
    pthread_mutex_t * lpCriticalSection
    );        
    

void
DeleteCriticalSection(
    pthread_mutex_t * lpCriticalSection
    );

#endif
