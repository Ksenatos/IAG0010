//
//  main.cpp
//  pretestik
//
//  Created by Paul on 09.09.17.
//  Copyright © 2017 Paul. All rights reserved.
//

#include "Pretest.h"
#include "stdio.h"
#include <iostream>

using namespace std;
#pragma warning (disable : 4996)

Object *o;

void PrintObjects(Header *pList)
{
    if (pList)
    {
        cout << pList->cBegin<<" objects=> \n";
        o = pList->pObject;
        function<void (Object*)> F = [&](Object *o1)
        {
            if (o1)
            {
                cout << o1->pID << " " << o1->Code << "\n";
                F(o1->pNext);
            }
        };
        F(o);
        PrintObjects (pList->pNext);
    }
}

int RemoveObject(Header **ppList, char *pExistingID, Header *preH)
{
    Header* pList = *ppList;
        if (*ppList)
        {
            if (pExistingID[0] == pList->cBegin)
            {
                o = pList->pObject;
                function<int (Object*, Object*)> F = [&](Object *o1, Object *pre)
                {
                    if (o1)
                        if (strcmp (pExistingID, o1->pID) == 0)
                        {
                            
                            cout << o1->pID <<"WOWOWOWOW\n";
                            pre->pNext = o1->pNext;
                            delete o1;
                            return 1;
                        }else
                        {
                            F(o1->pNext, o1);
                        }
                    return 0;
                };
                if (strcmp (pExistingID, o->pID) == 0)
                {
                    if (o->pNext)
                    {
                        cout << o->pID <<" ITS WORKING\n";
                        pList->pObject = o->pNext;
                        delete o;
                    }else
                    {
                        if (*ppList == preH)
                        {
                            cout << "HEREEEEE\n";
                            *ppList = pList->pNext;
                            delete pList;
                        }else
                        {
                            cout << pList->cBegin <<" <--remove it\n";
                            preH->pNext = pList->pNext;
                            delete pList;
                        }
                    }
                    return 1;
                }
                return F(o, o);
            } else
            {
                return RemoveObject(&pList->pNext, pExistingID, pList);
            }
        }else
            return 0;
}


int main()
{
    Header *pList = StructGenerator(25);
    PrintObjects(pList);
    char ExistingID[] = "Beebtheyy";
    cout << "\n" <<ExistingID << " --- "<< RemoveObject(&pList, ExistingID, pList) <<"\n"<<"--------------------------\n";
    char ExistingID2[] = "Btntvyh";
    cout << "\n" <<ExistingID2 << " --- "<< RemoveObject(&pList, ExistingID2, pList) <<"\n"<<"--------------------------\n";
    char ExistingID3[] = "415952";
    cout << "\n" <<ExistingID3 << " --- "<< RemoveObject(&pList, ExistingID3, pList) <<"\n"<<"--------------------------\n";
    
    PrintObjects(pList);

    //printf("Hello\n");
    return 0;
}
