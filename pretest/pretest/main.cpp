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

void PrintObjects(Header *pList, int num = 1)
{
    if (pList)
    {
        cout << pList->cBegin<<" objects=> \n";
        o = pList->pObject;
        function<void (Object*)> F = [&](Object *o)
        {
            if (o)
            {
                cout << num << ") " << o->pID << " " << o->Code << " " << o->pTime<<"\n";
                num++;
                F(o->pNext);
            }
        };
        F(o);
        PrintObjects (pList->pNext, num++);
    }
}


int RemoveObject(Header **ppList, char *pExistingID, Header *preH)
{
    Header* pList = *ppList;
        if (*ppList)
        {
            if (pExistingID[0] == pList->cBegin)                                        //choosing a header
            {
                o = pList->pObject;
                function<int (Object*, Object*)> F = [&](Object *o1, Object *pre)
                {
                    if (o1)
                        if (strcmp (pExistingID, o1->pID) == 0)
                        {
                            
                            cout << o1->pID <<"object removed\n";                            //remove object
                            pre->pNext = o1->pNext;
                            delete o1;
                            return 1;
                        } else
                        {
                            F(o1->pNext, o1);
                        }
                    return 0;
                };
                if (strcmp (pExistingID, o->pID) == 0)                                  //first object
                {
                    if (o->pNext)
                    {
                        cout << o->pID <<" first object removed\n";
                        pList->pObject = o->pNext;
                        delete o;
                    }else                                                              //only object in header
                    {
                        if (*ppList == preH)                                            //remove first header
                        {
                            cout << " first header remooved\n";
                            *ppList = pList->pNext;
                            delete pList;
                        }else                                                           //remove not first header
                        {
                            cout << pList->cBegin <<" header removed\n";
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
