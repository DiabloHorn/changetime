//This code may contain onused things.

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <winbase.h>
#include <shellapi.h>
//lolhieronderistest
#include <Wtsapi32.h>


BOOL CopyTime();

void main(int argc,char *argv[])
{
DWORD test;
DWORD dwAttrs;
HANDLE hFile;
HANDLE changeFile;
char tijd[500];

hFile = CreateFile(argv[1],
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

changeFile = CreateFile(argv[2],           // file to open
                GENERIC_WRITE,              // open for reading
                FILE_SHARE_READ,           // share for reading
                NULL,                      // default security
                OPEN_EXISTING,             // existing file only
                FILE_ATTRIBUTE_NORMAL,     // normal file
                NULL);                     // no attr. template

CopyTime(hFile,tijd,changeFile);
CloseHandle(hFile);
CloseHandle(changeFile);

}

BOOL CopyTime(HANDLE hFile, LPSTR lpszString,HANDLE file2change)
{
    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stUTC, stLocal;

    // Retrieve the file times for the file.
    if (!GetFileTime(hFile, &ftCreate,&ftAccess, &ftWrite))
        return FALSE;
	//take other files time
	SetFileTime(file2change,&ftCreate,&ftAccess, &ftWrite);
    // Convert the last-write time to local time.
    FileTimeToSystemTime(&ftWrite, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    // Build a string showing the date and time.
    wsprintf(lpszString, "%02d/%02d/%d  %02d:%02d",
        stLocal.wDay, stLocal.wMonth, stLocal.wYear,
        stLocal.wHour, stLocal.wMinute);

    return TRUE;
}
