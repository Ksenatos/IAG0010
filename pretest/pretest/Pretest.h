#pragma once

typedef struct Object
{
	char* pID;
	unsigned long int Code;
	char* pTime;
	Object *pNext;
}Object;

typedef struct Header
{
	Object* pObject;
	char cBegin;
	Header *pNext;
}Header;

Header *StructGenerator(int nObject);
