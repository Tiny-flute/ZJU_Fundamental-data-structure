//
//  PTA_practice.h
//  week_1
//
//  Created by 曲耕余 on 2021/10/6.
//

#ifndef PTA_practice_h
#define PTA_practice_h
#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;
/* Nodes are sorted in decreasing order of exponents.*/
Polynomial Read(void); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );
#endif /* PTA_practice_h */
