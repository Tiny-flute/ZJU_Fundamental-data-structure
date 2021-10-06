//
//  reverse linked list.h
//  week_1
//
//  Created by 曲耕余 on 2021/10/6.
//

#ifndef reverse_linked_list_h
#define reverse_linked_list_h
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

#endif /* reverse_linked_list_h */
