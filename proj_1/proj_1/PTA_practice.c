//
//  PTA_practice.c
//  week_1
//
//  Created by 曲耕余 on 2021/10/6.
//

#include "PTA_practice.h"
Polynomial Add( Polynomial a, Polynomial b )   // add polynomials with linked list
{
    Polynomial head_a = a, head_b = b,result_head,result;
    if(head_a->Next == NULL)
        return b;
    if(head_b->Next == NULL)
        return a;
    result_head  = malloc(sizeof(struct Node));
    result = result_head;
    b = b->Next;
    a = a->Next;
        for(;a && b;)
        {
            if(b->Exponent < a->Exponent)
            {
                result ->Next = malloc(sizeof(struct Node));
                result = result->Next;
                result->Coefficient = a->Coefficient;
                result->Exponent = a->Exponent;
                result->Next = NULL;
                a = a->Next;
            }
            else if(b->Exponent == a->Exponent)
            {
                if(a->Coefficient + b->Coefficient == 0)
                {
                    a = a->Next;
                    b = b->Next;
                    continue;
                }
                result ->Next = malloc(sizeof(struct Node));
                result = result->Next;
                result->Exponent = b->Exponent;
                result->Coefficient = a->Coefficient + b->Coefficient;
                result->Next = NULL;
                a = a->Next;
                b = b->Next;
            }
            else
            {
                result ->Next = malloc(sizeof(struct Node));
                result = result->Next;
                result->Exponent = b->Exponent;
                result->Coefficient = b->Coefficient;
                result->Next = NULL;
                b = b->Next;
            }
        }
    if(a == NULL)
    {
        for(;b;)
        {
            result ->Next = malloc(sizeof(struct Node));
            result = result->Next;
            result->Exponent = b->Exponent;
            result->Coefficient = b->Coefficient;
            result->Next = NULL;
            b = b->Next;
        }
    }
    else if(b == NULL)
    {
        for(;a;)
        {
            result ->Next = malloc(sizeof(struct Node));
            result = result->Next;
            result->Coefficient = a->Coefficient;
            result->Exponent = a->Exponent;
            result->Next = NULL;
            a = a->Next;
        }
    }
    return result_head;
}
