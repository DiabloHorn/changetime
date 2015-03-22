#include <stdio.h>
#include <shellapi.h>

BOOL CopyTime();

void main(int argc,char *argv[])
{
DWORD test;
DWORD dwAttrs;
HANDLE hFile;
HANDLE changeFile;
HANDLE clipData;
char tijd[500];
char sysdir[MAX_PATH];
char path[MAX_PATH];
GetSystemDirectory(sysdir, sizeof(sysdir));
sprintf(path,"%s\\svchost.exe",sysdir);

hFile = CreateFile(path,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

changeFile = CreateFile(argv[1],           // file to open
                GENERIC_WRITE,              // open for reading
                FILE_SHARE_READ,           // share for reading
                NULL,                      // default security
                OPEN_EXISTING,             // existing file only
                FILE_ATTRIBUTE_NORMAL,     // normal file
                NULL);                     // no attr. template

CopyTime(hFile,tijd,changeFile);
//you can print the file time by doing:
//printf("%s",tijd);

}

BOOL CopyTime(HANDLE hFile, LPSTR lpszString,HANDLE file2change)
{
    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stUTC, stLocal;

    // Retrieve the file times for the file.
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
        return FALSE;
	//take other files time
	SetFileTime(file2change,&ftCreate, &ftAccess, &ftWrite);
    // Convert the last-write time to local time.
    FileTimeToSystemTime(&ftWrite, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    // Build a string showing the date and time.
    wsprintf(lpszString, "%02d/%02d/%d  %02d:%02d",
        stLocal.wDay, stLocal.wMonth, stLocal.wYear,
        stLocal.wHour, stLocal.wMinute);

    return TRUE;
}
