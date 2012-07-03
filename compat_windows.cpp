#include "compat_windows.h"
#include <unistd.h>
#include <string.h>
#include "iniparser.h"

unsigned long GetPrivateProfileString(
    const char * lpAppName,
    const char * lpKeyName,
    const char * lpDefault,
    char * lpReturnedString,
    unsigned long nSize,
    const char * lpFileName
    )
{
  if(lpAppName==NULL || lpKeyName==NULL) return 0;
  dictionary * ini;
  ini = iniparser_load((char *)lpFileName);
  char *key = new char[strlen(lpAppName)+strlen(lpKeyName)+2];
  sprintf(key,"%s:%s",lpAppName,lpKeyName);
  char *str=iniparser_getstring(ini,key,(char *)lpDefault);
  if(str!=NULL) strncpy(lpReturnedString,str,nSize);
  delete []key;
  iniparser_freedict(ini);
  return strlen(lpReturnedString);
}

unsigned long GetCurrentDirectory(
     unsigned long nBufferLength,
     char * lpBuffer
    )
{
  if(getcwd(lpBuffer,nBufferLength)==NULL) return 0;
  return strlen(lpBuffer);
}

void Sleep(
     unsigned long dwMilliseconds
    )
{
  usleep(dwMilliseconds);
}

void
InitializeCriticalSection(
    pthread_mutex_t * lpCriticalSection
    )
{
	pthread_mutex_init(lpCriticalSection,NULL);
}    
 
void
EnterCriticalSection(
    pthread_mutex_t * lpCriticalSection
    )
{
	pthread_mutex_lock(lpCriticalSection);
}    
    
void
LeaveCriticalSection(
    pthread_mutex_t * lpCriticalSection
    )
{
	pthread_mutex_unlock(lpCriticalSection);
}

void
DeleteCriticalSection(
    pthread_mutex_t * lpCriticalSection
    )
{
	pthread_mutex_destroy(lpCriticalSection);
}

