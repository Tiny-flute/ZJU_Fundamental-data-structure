//
//  reverse linked list.c
//  week_1
//
//  Created by 曲耕余 on 2021/10/6.
//
#include "reverse linked list.h"

List Reverse(List L)
{
    List Last = NULL, temp;
    List head = L;
    L = L->Next;
    for(;L;)
    {
        temp = L;
        L = L->Next;
        temp->Next = Last;
        Last = temp;
    }
    head->Next = Last;
    return head;
}
