#pragma once

struct Object
{
	char* pID;
	int Code;
	char* pTime;
	Object *pNext;
};
struct Header
{
	Object* pObject;
	char cBegin;
	Header *pNext;
};

Header *StructGenerator(int nObject);
