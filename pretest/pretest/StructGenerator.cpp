#include "Pretest.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
//#include "malloc.h"
#include "ctype.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

#pragma warning (disable : 4996 )

char *CreateRandomWord(int nResult, int seed);
char *GetTime();
Object *CreateObject(int i);
Header *CreateHeader(Object *pNewObject);

Header *StructGenerator(int nObject)
{
	if (!nObject)
		return 0;
	Header *pResult = 0, *p, *p1, *p2;
	for (int i = 0;  i < nObject;  i++)
	{
		Object *pNewObject = CreateObject(i);
		if (!i)
		{
			pResult = CreateHeader(pNewObject);
			continue;
		}
     
		for (p = pResult;  p && p->cBegin != *pNewObject->pID;  p = p->pNext);
		if (p)
		{
            pNewObject->pNext = p->pObject;
			p->pObject = pNewObject;
			continue;
        }else{
        }
		Header *pNewHeader = CreateHeader(pNewObject);
		for (p1 = pResult, p2 = 0;  p1 && p1->cBegin < *pNewObject->pID;  p2 = p1, p1 = p1->pNext);
		if (!p2)
		{
			pNewHeader->pNext = pResult;
			pResult = pNewHeader;
		}
		else
		{
			pNewHeader->pNext = p1;
			p2->pNext = pNewHeader;
		}

        
	}
    return pResult;
}

char *CreateRandomWord(int nResult, int seed)
{
	const char *pLetters = "bcdefghijklmnopqrstuvwxy";
	char *pResult = (char *)malloc(nResult + 1);
	srand(seed);
	for (int i = 0;  i < nResult;  i++)
		*(pResult + i) = pLetters[rand() % 24];
	*pResult = toupper(*pResult);
    *(pResult + nResult) = 0;
	return pResult;
}

char *GetTime()
{
	time_t RawTime;
	time(&RawTime);
	struct tm tmTime;
    localtime_r(&RawTime, &tmTime);
	char *pResult = (char *)malloc(10);
	sprintf(pResult, "%02d:%02d:%02d", tmTime.tm_hour, tmTime.tm_min, tmTime.tm_sec);
	return pResult;
}

Object *CreateObject(int i)
{
	Object *pNewObject = (Object *)malloc(sizeof (Object));
    pNewObject->pID = CreateRandomWord(i % 5 + 5, i * i);
	pNewObject->Code = i;
	pNewObject->pTime = GetTime();
	pNewObject->pNext = 0;
	return pNewObject;
}

Header *CreateHeader(Object *pNewObject)
{
	Header *pNewHeader = (Header *)malloc(sizeof (Header));
	pNewHeader->pObject = pNewObject;
	pNewHeader->cBegin = *pNewObject->pID;
	pNewHeader->pNext = 0;
	return pNewHeader;
}

